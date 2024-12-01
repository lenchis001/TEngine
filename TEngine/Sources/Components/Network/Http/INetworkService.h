#ifndef TENGINE_NETWORK_HTTP_INETWORKSERVICE_H
#define TENGINE_NETWORK_HTTP_INETWORKSERVICE_H

#include "Models/Request.h"
#include "Models/Response.h"

#include <future>

namespace TEngine::Components::Network::Http
{
    class INetworkService
    {
    public:
        virtual ~INetworkService() = default;

        virtual Models::Response send(const Models::Request& request) = 0;
    };
}

#endif // TENGINE_NETWORK_HTTP_INETWORKSERVICE_H