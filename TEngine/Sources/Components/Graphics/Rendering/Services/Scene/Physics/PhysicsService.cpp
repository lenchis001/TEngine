#include "PhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics;

PhysicsService::PhysicsService() : _lastTime(0.0)
{
}

PhysicsService::~PhysicsService()
{
}

void PhysicsService::initialize()
{
    /// collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();

    /// use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);

    /// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();

    /// the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;

    _dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    _dynamicsWorld->setGravity(btVector3(0, -10.f, 0));
}

void PhysicsService::update(double time)
{
    static int counter = 1000;
    if (counter-- > 0)
    {
        return;
    }

    if (_lastTime == 0.0)
    {
        _lastTime = time;
    }

    auto deltaTime = time - _lastTime;
    _lastTime = time;

    _dynamicsWorld->stepSimulation(deltaTime, 10, 1.0 / 120.0);
    _syncRenderingState();
}

void PhysicsService::addStaticBox(
    const Vector3df &size,
    std::shared_ptr<IRenderingStrategy> renderingStrategy)
{
    btCollisionShape *groundShape = new btBoxShape(btVector3(size.getX(), size.getY(), size.getZ()));

    btScalar mass(0.);

    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);

    // using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState *myMotionState = new btDefaultMotionState();
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    btRigidBody *body = new btRigidBody(rbInfo);

    _objects[renderingStrategy] = body;

    // add the body to the dynamics world
    _dynamicsWorld->addRigidBody(body);
}

void PhysicsService::addDynamicBox(
    const Vector3df &size,
    std::shared_ptr<IRenderingStrategy> renderingStrategy)
{
    btCollisionShape *shape = new btBoxShape(btVector3(size.getX(), size.getY(), size.getZ()));

    /// Create Dynamic Objects
    btScalar mass(1.f);

    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);

    // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState *myMotionState = new btDefaultMotionState();
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    btRigidBody *body = new btRigidBody(rbInfo);

    _objects[renderingStrategy] = body;

    _dynamicsWorld->addRigidBody(body);
}

void PhysicsService::setPosition(
    const std::shared_ptr<IRenderingStrategy> renderingStrategy,
    const Vector3df &position)
{
    auto object = _objects.find(renderingStrategy);

    if (object != _objects.end())
    {
        btTransform transform;
        object->second->getMotionState()->getWorldTransform(transform);

        transform.setOrigin(btVector3(position.getX(), position.getY(), position.getZ()));

        object->second->setMotionState(new btDefaultMotionState(transform));
        object->second->activate(true);
    }
    else
    {
        assert(false && "Object not found");
    }
}

void PhysicsService::_syncRenderingState()
{
    for (auto &object : _objects)
    {
        btTransform transform;
        object.second->getMotionState()->getWorldTransform(transform);

        auto position = transform.getOrigin();
        auto rotation = transform.getRotation();

        object.first->setPosition(Vector3df(position.getX(), position.getY(), position.getZ()));
        object.first->setRotation(Vector3df(rotation.getX(), rotation.getY(), rotation.getZ()));
    }
}