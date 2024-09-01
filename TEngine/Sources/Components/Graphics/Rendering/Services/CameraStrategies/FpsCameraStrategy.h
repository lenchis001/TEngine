#include "memory"

#include "Components/Graphics/Models/Vector3d.h"

#include "Components/Events/Services/IEventService.h"

#include "CameraStrategyBase.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Events::Services;

namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies
{

    class FpsCameraStrategy : public CameraStrategyBase
    {
    public:
        FpsCameraStrategy(
            std::shared_ptr<IEventService> eventService,
            float fov,
            float aspectRatio,
            float zNear,
            float zFar,
            const Vector3df &position);
        ~FpsCameraStrategy() override;

        void render() override;

    private:
        bool _onMouseMoved(float x, float y);
        bool _onKeyWPressed(bool isPressed);
        bool _onKeySPressed(bool isPressed);
        bool _onKeyAPressed(bool isPressed);
        bool _onKeyDPressed(bool isPressed);
        bool _onKeyQPressed(bool isPressed);
        bool _onKeyEPressed(bool isPressed);
        bool _onKeyShiftPressed(bool isPressed);

        void _recalculateState();
        void _recalculateTarget();

        float _speed;
        float _phi, _theta, _radius;
        bool _isMovingForward, _isMovingBackward, _isMovingLeft, _isMovingRight, _isMovingUp, _isMovingDown, _isBoostActivated, _isRorated;
        Vector3df _position, _target;

        std::shared_ptr<IEventService> _eventService;

        std::vector<KeyboardEventHandler> _keyboardEventHandlers;
    };

}