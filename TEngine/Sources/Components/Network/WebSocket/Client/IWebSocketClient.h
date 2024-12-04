#ifndef TENGINE_NETWORK_WEBSOCKET_CLIENT_IWEBSOCKETCLIENT_H
#define TENGINE_NETWORK_WEBSOCKET_CLIENT_IWEBSOCKETCLIENT_H

#include <string>
#include <functional>
#include <map>
#include <future>

namespace TEngine::Components::Network::WebSocket::Client
{
    class IWebSocketClient
    {
    public:
        virtual ~IWebSocketClient() = default;

        virtual std::future<void> connect(const std::string &url, const std::map<std::string, std::string>& headers) = 0;

        virtual void send(const std::string &message) = 0;

        virtual void setOnMessageCallback(std::function<void(const std::string &message)> callback) = 0;

        virtual void close() = 0;
    };
}

#endif // TENGINE_NETWORK_WEBSOCKET_CLIENT_IWEBSOCKETCLIENT_H