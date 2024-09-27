#include "PhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics;

PhysicsService::PhysicsService():
_lastTime(0.0)
{
}

PhysicsService::~PhysicsService()
{
}

void PhysicsService::initialize()
{
    // Initialize Bullet Physics world
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    _dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    _dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void PhysicsService::update(double time)
{
    if (_lastTime == 0.0)
    {
        _lastTime = time;
    }

    auto deltaTime = time - _lastTime;

    _dynamicsWorld->stepSimulation(deltaTime, 10);
}