#include "IWebSocketClient.h"

#include <thread>
#include <memory>

#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/client.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

namespace TEngine::Components::Network::WebSocket::Client
{
    class WebSocketClient : public IWebSocketClient
    {
    public:
        WebSocketClient();
        
        ~WebSocketClient() override;

        std::future<void> connect(const std::string &url, const std::map<std::string, std::string>& headers) override;

        void send(const std::string &message) override;
        
        void setOnMessageCallback(std::function<void(const std::string &message)> callback) override;
        
        void close() override;

    private:
        std::function<void(const std::string &message)> _onMessageCallback;

        websocketpp::connection_hdl _handler;
        std::shared_ptr<client> _client;
        std::shared_ptr<std::thread> _socketThread;
    };
}