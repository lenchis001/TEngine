#include "memory"



namespace TEngine::Components::Graphics::Rendering::Services::Strategies
{
    class IRenderingStrategyFactory
    {
    public:
        virtual std::shared_ptr<IRenderingStrategy> create() = 0;

        virtual ~IRenderingStrategyFactory() = default;
    };
}