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

    _dynamicsWorld->stepSimulation(deltaTime, 10, 1.0 / 60.0);
    _syncRenderingState();
}

void PhysicsService::addBox(
    std::shared_ptr<IRenderingStrategy> renderingStrategy,
    float mass)
{
    auto halfSize = _getSize(renderingStrategy->getVertices()) / 2.f;

    btCollisionShape *groundShape = new btBoxShape(btVector3(halfSize.getX(), halfSize.getY(), halfSize.getZ()));

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

Vector3df PhysicsService::_getSize(const std::vector<float> &vertices)
{
    float minX = 0;
    float minY = 0;
    float minZ = 0;

    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;

    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        auto x = vertices[i];
        auto y = vertices[i + 1];
        auto z = vertices[i + 2];

        if (x < minX)
        {
            minX = x;
        }

        if (y < minY)
        {
            minY = y;
        }

        if (z < minZ)
        {
            minZ = z;
        }

        if (x > maxX)
        {
            maxX = x;
        }

        if (y > maxY)
        {
            maxY = y;
        }

        if (z > maxZ)
        {
            maxZ = z;
        }
    }

    return Vector3df(maxX - minX, maxY - minY, maxZ - minZ);
}