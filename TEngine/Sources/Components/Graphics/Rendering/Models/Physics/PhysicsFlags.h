#ifndef TENGINE_PHYSICSFLAGS_H
#define TENGINE_PHYSICSFLAGS_H

namespace TEngine::Components::Graphics::Rendering::Models::Physics
{
    enum class PhysicsFlags : int {
        NONE = 0,
        STATIC = 1,
        DYNAMIC = 2
    };
}

#endif // TENGINE_PHYSICSFLAGS_H