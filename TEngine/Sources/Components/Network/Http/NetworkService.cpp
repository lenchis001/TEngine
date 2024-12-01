#include "NetworkService.h"

#include <stdexcept>
#include <iostream>

#include <boost/asio.hpp>

using namespace TEngine::Components::Network::Http;

Response NetworkService::send(const Request &request)
{
    try
    {
        std::string url = request.getUrl();
        if (url.find("http://") != 0 && url.find("https://") != 0)
        {
            throw std::invalid_argument("Invalid URL: " + url);
        }

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(url, "http");

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        auto method = request.getMethod();
        std::string req = getMethodString(method);
        req += request.getUrl() + " HTTP/1.1\r\n";
        for (const auto &header : request.getHeaders())
        {
            req += header.first + ": " + header.second + "\r\n";
        }

        if (method == Methods::POST || method == Methods::PUT)
        {
            req += "Content-Type: application/json\r\n";
        }
        req += "\r\n" + request.getData();

        boost::asio::write(socket, boost::asio::buffer(req));

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        std::map<std::string, std::string> headers;
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
        {
            auto colon_pos = header.find(": ");
            if (colon_pos != std::string::npos)
            {
                headers[header.substr(0, colon_pos)] = header.substr(colon_pos + 2);
            }
        }

        std::string body;
        if (response.size() > 0)
        {
            std::ostringstream ss;
            ss << &response;
            body = ss.str();
        }

        return Response(status_code, body, headers);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return Response(500, "Internal Server Error", {});
    }
}

std::string NetworkService::getMethodString(Methods method)
{
    switch (method)
    {
    case Methods::GET:
        return "GET";
    case Methods::POST:
        return "POST";
    case Methods::PUT:
        return "PUT";
    case Methods::DELETE:
        return "DELETE";
    default:
        throw std::invalid_argument("Invalid method");
    }
}