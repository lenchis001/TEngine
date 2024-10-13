#ifndef ALICE_IPRESENTER_H
#define ALICE_IPRESENTER_H

namespace Alice::Core
{
    template<class VT> class IPresenter
    {
    public:
        virtual void injectView(VT* view) = 0;

        virtual ~IPresenter() = default;
    };
}

#endif // ALICE_IPRESENTER_H