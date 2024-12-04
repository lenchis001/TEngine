#ifndef TENGINE_IWEBSOCKETFACTORY_H
#define TENGINE_IWEBSOCKETFACTORY_H

#include <memory>

#include "Client/IWebSocketClient.h"

namespace TEngine::Components::Network::WebSocket
{
    class IWebSocketFactory
    {
    public:
        virtual ~IWebSocketFactory() = default;

        virtual std::shared_ptr<Client::IWebSocketClient> createClient() = 0;
    };
}

#endif // TENGINE_IWEBSOCKETFACTORY_H