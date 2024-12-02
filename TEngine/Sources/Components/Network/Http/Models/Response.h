#ifndef TENGINE_RESPONSE_H
#define TENGINE_RESPONSE_H

#include <string>
#include <map>

#include "Configs/TEngineExport.h"

namespace TEngine::Components::Network::Http::Models
{
    class TENGINE_API Response
    {
    public:
        Response(int status, std::string body, std::map<std::string, std::string> headers);

        int getStatus();

        std::string getBody();

        std::map<std::string, std::string> getHeaders();

    private:
        int _status;
        std::string _body;
        std::map<std::string, std::string> _headers;
    };
}

#endif // TENGINE_RESPONSE_H