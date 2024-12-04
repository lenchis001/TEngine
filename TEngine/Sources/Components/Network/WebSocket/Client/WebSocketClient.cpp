#include "WebSocketClient.h"
#include <iostream>

using namespace TEngine::Components::Network::WebSocket::Client;

WebSocketClient::WebSocketClient()
    : _client(nullptr), _socketThread(nullptr)
{
}

WebSocketClient::~WebSocketClient()
{
    close();
}

std::future<void> WebSocketClient::connect(const std::string &url, const std::map<std::string, std::string> &headers)
{
    auto promise = std::make_shared<std::promise<void>>();

    // Create a client endpoint
    _client = std::make_shared<client>();

    _client->clear_access_channels(websocketpp::log::alevel::all);

    _client->set_open_handler(
        [&, promise](websocketpp::connection_hdl handler)
        {
            _handler = handler;
            promise->set_value();
        });

    // Initialize ASIO
    _client->init_asio();

    _client->set_message_handler(
        [&](websocketpp::connection_hdl, message_ptr message)
        {
            if (_onMessageCallback)
            {
                _onMessageCallback(message->get_payload());
            }
        });

    websocketpp::lib::error_code ec;
    client::connection_ptr con = _client->get_connection(url, ec);

    for (auto &header : headers)
    {
        con->append_header(header.first, header.second);
    }

    _client->connect(con);

    _socketThread = std::make_shared<std::thread>(
        [&]()
        {
            _client->run();
        });

    return promise->get_future();
}

void WebSocketClient::send(const std::string &message)
{
    _client->send(_handler, message, websocketpp::frame::opcode::value::text);
}

void WebSocketClient::setOnMessageCallback(std::function<void(const std::string &message)> callback)
{
    _onMessageCallback = callback;
}

void WebSocketClient::close()
{
    if (_client)
    {
        _client->close(_handler, websocketpp::close::status::normal, "");
        _socketThread->join();

        _client = nullptr;
        _socketThread = nullptr;
    }
}