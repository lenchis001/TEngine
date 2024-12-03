#include "INetworkService.h"

using namespace TEngine::Components::Network::Http::Models;

namespace TEngine::Components::Network::Http
{
    class NetworkService : public INetworkService
    {
    public:
        Response send(const Request &request) override;
    };
}