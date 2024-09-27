#include "memory"
#include "vector"

#include "Components/Graphics/Models/Vector3d.h"

#include "Components/Events/Services/IEventService.h"

#include "CameraStrategyBase.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Events::Services;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies
{

    class FpsCameraStrategy : public CameraStrategyBase
    {
    public:
        FpsCameraStrategy(
            std::shared_ptr<IEventService> eventService,
            float fov,
            const Vector2di &windowSize,
            float zNear,
            float zFar,
            const Vector3df &position);
        ~FpsCameraStrategy() override;

        void render(double time) override;

        void setWindowSize(const Vector2di &value) override;

    private:
        bool _onKeyPressed(int key, int scancode, int action, int mods);
        bool _onMouseMoved(float x, float y);

        void _recalculateState(double time);
        void _recalculateTarget();

        float _speed;
        float _phi, _theta, _radius;
        bool _isMovingForward, _isMovingBackward, _isMovingLeft, _isMovingRight, _isMovingUp, _isMovingDown, _isBoostActivated, _isRorated;
        Vector3df _position, _target;
        Vector2di _windowCenter;
        double _lastTime;

        std::shared_ptr<IEventService> _eventService;

        std::vector<KeyboardEventHandler> _keyboardEventHandlers;
    };

}