#include "NetworkService.h"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <curl/curl.h>

using namespace TEngine::Components::Network::Http;

Response NetworkService::send(const Request &request)
{
    try
    {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (!curl)
        {
            throw std::runtime_error("Failed to initialize CURL");
        }

        std::string url = request.getUrl();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        struct curl_slist *headers = nullptr;
        for (const auto &header : request.getHeaders())
        {
            headers = curl_slist_append(headers, (header.first + ": " + header.second).c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        if (request.getMethod() == Methods::POST || request.getMethod() == Methods::PUT)
        {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.getData().c_str());
            if (request.getMethod() == Methods::POST)
            {
                curl_easy_setopt(curl, CURLOPT_POST, 1L);
            }
            else
            {
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            }
        }
        else if (request.getMethod() == Methods::DEL)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }

        std::ostringstream response_stream;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void *contents, size_t size, size_t nmemb, void *userp) -> size_t {
            ((std::ostringstream *)userp)->write((char *)contents, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_stream);

        std::map<std::string, std::string> response_headers;
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, +[](void *contents, size_t size, size_t nmemb, void *userp) -> size_t {
            std::string header((char *)contents, size * nmemb);
            auto colon_pos = header.find(':');
            if (colon_pos != std::string::npos)
            {
                std::string key = header.substr(0, colon_pos);
                std::string value = header.substr(colon_pos + 1);
                value.erase(0, value.find_first_not_of(" \t\r\n"));
                value.erase(value.find_last_not_of(" \t\r\n") + 1);
                ((std::map<std::string, std::string> *)userp)->emplace(key, value);
            }
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            curl_easy_cleanup(curl);
            throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
        }

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return Response(response_code, response_stream.str(), response_headers);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return Response(-1, e.what(), {});
    }
}