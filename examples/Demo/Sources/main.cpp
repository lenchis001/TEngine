#include "IEngine.h"

int main() {
    auto engine = TEngine::createEngine();

    auto creationParameters = TEngine::Models::EngineParameters();
    engine->initialize(creationParameters);

    while (true)
    {
        engine->getGraphicsService()->render();
    }
    
    return 0;
}