#ifndef TENGINE_BIG_WORLD_PARAMETERS_H
#define TENGINE_BIG_WORLD_PARAMETERS_H

#include "IBigWorldParameters.h"

namespace TEngine::Components::Graphics::Rendering::Models::Optimization
{
    class BigWorldParameters : public IBigWorldParameters
    {
    public:
        BigWorldParameters();
        ~BigWorldParameters() override = default;

        void setVisibilityTreshold(unsigned int value) override;

        unsigned int getVisibilityTreshold() const override;

        void setTrakingFrequency(unsigned int value) override;

        unsigned int getTrakingFrequency() const override;

        void setQueriesAmount(unsigned int value) override;

        unsigned int getQueriesAmount() const override;

        void setEnabled(bool value) override;

        bool isEnabled() const override;

    private:
        unsigned int _visibilityTreshold;
        unsigned int _trakingFrequency;
        unsigned int _queriesAmount;
        bool _isEnabled;
    };
}

#endif // TENGINE_BIG_WORLD_PARAMETERS_H