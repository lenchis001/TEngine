#ifndef TENGINE_MIXINS_TYPEINFOAWARE_H
#define TENGINE_MIXINS_TYPEINFOAWARE_H

#include <typeindex>

namespace TEngine::Mixins
{
    class TypeInfoAware
    {
    public:
        virtual std::type_index getType() const = 0;
    };
}

#endif // TENGINE_MIXINS_TYPEINFOAWARE_H