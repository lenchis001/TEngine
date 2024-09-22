#ifndef TENGINE_IGUISERVICE_H
#define TENGINE_IGUISERVICE_H

namespace TEngine::Components::Graphics::Rendering::Services::Gui
{
    class IGuiService
    {
    public:
        virtual ~IGuiService() = default;

        virtual void initialize() = 0;

        virtual void render() = 0;
    };
}

#endif // TENGINE_IGUISERVICE_H