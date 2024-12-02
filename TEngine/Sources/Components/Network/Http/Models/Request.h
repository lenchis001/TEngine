#ifndef TENGINE_REQUEST_H
#define TENGINE_REQUEST_H

#include <string>
#include <map>

#include "Configs/TEngineExport.h"

#include "Methods.h"

namespace TEngine::Components::Network::Http::Models
{
    class TENGINE_API Request
    {
    public:
        Request(const std::string &url, const std::string &data, Methods method, std::map<std::string, std::string> headers);

        const std::string &getUrl() const;

        const std::string &getData() const;

        Methods getMethod() const;

        const std::map<std::string, std::string> &getHeaders() const;

    private:
        std::string _url;
        std::string _data;
        Methods _method;
        std::map<std::string, std::string> _headers;
    };
}

#endif // TENGINE_REQUEST_H