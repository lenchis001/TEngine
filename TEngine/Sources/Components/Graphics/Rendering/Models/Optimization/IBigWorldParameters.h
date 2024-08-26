#ifndef TENGINE_IBIG_WORLD_PARAMETERS_H
#define TENGINE_IBIG_WORLD_PARAMETERS_H

namespace TEngine::Components::Graphics::Rendering::Models::Optimization
{
    class IBigWorldParameters
    {
    public:
        virtual void setVisibilityTreshold(unsigned int value) = 0;

        virtual unsigned int getVisibilityTreshold() const = 0;

        virtual void setTrakingFrequency(unsigned int value) = 0;

        virtual unsigned int getTrakingFrequency() const = 0;

        virtual unsigned setQueriesAmount(unsigned int value) = 0;

        virtual unsigned getQueriesAmount() const = 0;

        virtual void setEnabled(bool value) = 0;

        virtual bool isEnabled() const = 0;

        virtual ~IBigWorldParameters() = default;
    };
}

#endif // TENGINE_IBIG_WORLD_PARAMETERS_H