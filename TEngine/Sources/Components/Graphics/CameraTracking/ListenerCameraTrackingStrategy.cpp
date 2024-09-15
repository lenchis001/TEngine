#include "ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics::CameraTracking;

ListenerCameraTrackingStrategy::ListenerCameraTrackingStrategy(std::shared_ptr<IAudioService> audioService)
    : _audioService(audioService), _position(Vector3df(0, 0, 0))
{
}

void ListenerCameraTrackingStrategy::onPositionUpdated(const Vector3df &position)
{
    _audioService->setListenerPosition(position.getX(), position.getY(), position.getZ());

    _position = position;
}

void ListenerCameraTrackingStrategy::onTargetUpdated(const Vector3df &target)
{
    auto direction = (_position - target).getNormalized();

    _audioService->setListenerRotation(direction.getX(), direction.getY(), direction.getZ());
}