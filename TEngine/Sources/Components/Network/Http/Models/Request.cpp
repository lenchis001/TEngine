#include "Request.h"

using namespace TEngine::Components::Network::Http::Models;

Request::Request(const std::string &url, const std::string &data, Methods method, std::map<std::string, std::string> headers)
    : _url(url), _data(data), _method(method), _headers(headers)
{
}

const std::string &Request::getUrl() const
{
    return _url;
}

const std::string &Request::getData() const
{
    return _data;
}

Methods Request::getMethod() const
{
    return _method;
}

const std::map<std::string, std::string> &Request::getHeaders() const
{
    return _headers;
}