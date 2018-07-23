#ifndef TENGINE_IRENDERINGSERVICE_H
#define TENGINE_IRENDERINGSERVICE_H

namespace TEngine::Components::Graphics::Services::Rendering
{
    class IRenderingService
    {
    public:
        virtual void render() = 0;

        virtual ~IRenderingService() = default;
    };
}

#endif //TENGINE_IRENDERINGSERVICE_H