#include "Response.h"

using namespace TEngine::Components::Network::Http::Models;

Response::Response(int status, std::string body, std::map<std::string, std::string> headers)
    : _status(status), _body(body), _headers(headers)
{
}

int Response::getStatus()
{
    return _status;
}

std::string Response::getBody()
{
    return _body;
}

std::map<std::string, std::string> Response::getHeaders()
{
    return _headers;
}