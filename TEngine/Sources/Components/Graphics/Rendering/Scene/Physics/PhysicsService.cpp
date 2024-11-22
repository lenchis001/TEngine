#include "PhysicsService.h"

#include <cassert>

using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

PhysicsService::PhysicsService() : _lastTime(0.0)
{
}

PhysicsService::~PhysicsService()
{
    assert(_objects.empty() && "Not all objects were removed from the physics service");

    delete _dynamicsWorld;
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
    if (_lastTime == 0.0)
    {
        _lastTime = time;
    }

    auto deltaTime = time - _lastTime;
    _lastTime = time;

    _dynamicsWorld->stepSimulation(deltaTime, 10, 1.0 / 60.0);
    _syncRenderingState();
}

bool PhysicsService::isAttached(
    std::shared_ptr<IPhysicsRenderingAware> renderingStrategy)
{
    return _objects.find(renderingStrategy) != _objects.end();
}

void PhysicsService::addBox(
    std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
    float mass)
{
    assert(_objects.find(renderingStrategy) == _objects.end() && "Object already exists");

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

void PhysicsService::removeBox(
    std::shared_ptr<IPhysicsRenderingAware> renderingStrategy)
{
    auto object = _objects.find(renderingStrategy);

    if (object != _objects.end())
    {
        _dynamicsWorld->removeRigidBody(object->second);

        delete object->second->getMotionState();
        delete object->second->getCollisionShape();
        delete object->second;

        _objects.erase(object);
    }
    else
    {
        assert(false && "Object not found");
    }
}

void PhysicsService::setPosition(
    const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
    const Vector3df &position)
{
    auto object = _objects.find(renderingStrategy);

    if (object != _objects.end())
    {
        btTransform transform;
        object->second->getMotionState()->getWorldTransform(transform);

        transform.setOrigin(btVector3(position.getX(), position.getY(), position.getZ()));

        delete object->second->getMotionState();
        object->second->setMotionState(new btDefaultMotionState(transform));
        object->second->activate(true);
    }
    else
    {
        assert(false && "Object not found");
    }
}

void PhysicsService::setRotation(
    const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
    const Vector3df &rotation)
{
    auto object = _objects.find(renderingStrategy);

    if (object != _objects.end())
    {
        btTransform transform;
        object->second->getMotionState()->getWorldTransform(transform);

        // We need to multiply by 2 because bullet physics uses twice more rotation than we do
        auto btRotation = rotation * 2;

        transform.setRotation(btQuaternion(btRotation.getY(), btRotation.getX(), btRotation.getZ()));

        delete object->second->getMotionState();
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
        object.first->setDirectAbsolutePosition(Vector3df(position.getX(), position.getY(), position.getZ()));

        btScalar x, y, z;
        transform.getRotation().getEulerZYX(z, y, x);
        object.first->setDirectAbsoluteRotation(Vector3df(x, y, z) / 2);
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