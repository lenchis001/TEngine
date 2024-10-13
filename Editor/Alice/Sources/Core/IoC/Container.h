#ifndef ALICE_ICONTAINER_H
#define ALICE_ICONTAINER_H

#include <memory>
#include <functional>
#include <unordered_map>
#include <typeindex>

namespace Alice::Core::IoC
{
    class Container
    {
    public:
        template <class T>
        void registerType(std::function<T*(Container *)> factory)
        {
            _factories[std::type_index(typeid(T))] = [factory](Container *container)
            {
                return static_cast<void*>(factory(container));
            };
        }

        template <class T>
        T* resolve()
        {
            auto factory = _factories[std::type_index(typeid(T))];
            return static_cast<T*>(factory(this));
        }

    private:
        std::unordered_map<std::type_index, std::function<void*(Container *)>> _factories;
    };
}

#endif // ALICE_ICONTAINER_H