#include "WebSocketFactory.h"

#include "Client/WebSocketClient.h"

using namespace TEngine::Components::Network::WebSocket;
using namespace TEngine::Components::Network::WebSocket::Client;

std::shared_ptr<IWebSocketClient> WebSocketFactory::createClient()
{
    return std::make_shared<WebSocketClient>();
}