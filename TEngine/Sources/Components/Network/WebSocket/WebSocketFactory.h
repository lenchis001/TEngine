#include "IWebSocketFactory.h"

using namespace TEngine::Components::Network::WebSocket::Client;

namespace TEngine::Components::Network::WebSocket
{
    class WebSocketFactory : public IWebSocketFactory
    {
    public:
        ~WebSocketFactory() override = default;

        std::shared_ptr<IWebSocketClient> createClient() override;
    };
}