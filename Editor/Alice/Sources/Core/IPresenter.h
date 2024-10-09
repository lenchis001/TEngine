#ifndef ALICE_IPRESENTER_H
#define ALICE_IPRESENTER_H

#include <memory>

namespace Alice::Core
{
    template<class VT> class IPresenter
    {
    public:
        virtual void injectView(std::weak_ptr<VT> view) = 0;

        virtual ~IPresenter() = default;
    };
}

#endif // ALICE_IPRESENTER_H