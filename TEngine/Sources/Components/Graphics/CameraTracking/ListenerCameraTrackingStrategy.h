#include <memory>

#include "Components/Graphics/Rendering/Scene/CameraStrategies/Tracking/ICameraTrackingStrategy.h"

#include "Components/Audio/Services/IAudioService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies::Tracking;
using namespace TEngine::Components::Audio::Services;

namespace TEngine::Components::Graphics::CameraTracking
{
    class ListenerCameraTrackingStrategy : public ICameraTrackingStrategy
    {
    public:
        ListenerCameraTrackingStrategy(std::shared_ptr<IAudioService> audioService);

        void onPositionUpdated(const Vector3df &position) override;

        void onTargetUpdated(const Vector3df &target) override;

    private:
        std::shared_ptr<IAudioService> _audioService;

        Vector3df _position;
    };
}