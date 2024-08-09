#ifndef TENGINE_IRENDERINGSTRATEGY_H
#define TENGINE_IRENDERINGSTRATEGY_H

namespace TEngine::Components::Graphics::Rendering::Services::Strategies
{
    class IRenderingStrategy
    {
    public:
        virtual void render() = 0;

        virtual ~IRenderingStrategy() = default;
    };
}

#endif // TENGINE_IRENDERINGSTRATEGY_H