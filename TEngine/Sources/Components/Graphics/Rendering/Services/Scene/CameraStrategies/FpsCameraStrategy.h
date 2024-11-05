#ifndef TENGINE_FPS_CAMERA_STRATEGY_H
#define TENGINE_FPS_CAMERA_STRATEGY_H

#include <memory>
#include <vector>

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

    protected:
        virtual bool _onMouseMoved(float x, float y);

        float _phi, _theta;
        bool _isRorated;

        std::shared_ptr<IEventService> _eventService;

    private:
        bool _onKeyPressed(int key, int scancode, int action, int mods);

        void _recalculateState(double time);
        void _recalculateTarget();

        float _speed;
        float _radius;
        bool _isMovingForward, _isMovingBackward, _isMovingLeft, _isMovingRight, _isMovingUp, _isMovingDown, _isBoostActivated;
        Vector3df _position, _target;
        Vector2di _windowCenter;
        double _lastTime;

        std::vector<KeyboardEventHandler> _keyboardEventHandlers;
    };

}

#endif // TENGINE_FPS_CAMERA_STRATEGY_H