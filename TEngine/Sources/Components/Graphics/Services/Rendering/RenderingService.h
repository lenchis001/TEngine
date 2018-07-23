#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

namespace TEngine::Components::Graphics::Services::Rendering
{
    class RenderingService : public IRenderingService
    {
    public:
        void render() override;
    private:
        
    };
}

#endif //TENGINE_RENDERINGSERVICE_H