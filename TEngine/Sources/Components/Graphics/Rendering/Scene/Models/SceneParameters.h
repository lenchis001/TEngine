#include "ISceneParameters.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Models
{
    class SceneParameters : public ISceneParameters
    {
    public:
        SceneParameters();

        float getSequenceUpdateThreshold() const override;

        void setSequenceUpdateThreshold(float sequenceUpdateThreshold) override;

    private:
        float _sequenceUpdateThreshold;
    };
}