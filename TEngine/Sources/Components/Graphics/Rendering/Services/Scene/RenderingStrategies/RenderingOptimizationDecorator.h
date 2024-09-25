#include "IRenderingStrategy.h"

#include "memory"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies
{
    class RenderingOptimizationDecorator : public IRenderingStrategy
    {
    public:
        RenderingOptimizationDecorator(std::shared_ptr<IRenderingStrategy> strategy);

        ~RenderingOptimizationDecorator() override = default;

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        void setPosition(const Vector3df &position) override;

        void setRotation(const Vector3df &rotation) override;

        void setScale(const Vector3df &scale) override;

        const Vector3df &getPosition() const override;

        const Vector3df &getRotation() const override;

        const Vector3df &getScale() const override;

        Vector3df getAbsolutePosition() override;

        const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const override;

        void addChild(std::shared_ptr<IRenderingStrategy> child) override;

        void removeChild(std::shared_ptr<IRenderingStrategy> child) override;

    protected:
        void _updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated = false) override;

    private:
        unsigned int _frameCounter;
        float _distance;
        std::shared_ptr<IRenderingStrategy> _strategy;
    };
}