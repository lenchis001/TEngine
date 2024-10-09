#ifndef ALICE_IVIEW_H
#define ALICE_IVIEW_H

#include <memory>

#include "IPresenter.h"

namespace Alice::Core
{
    template<class PT> class IView
    {
    public:
        virtual ~IView() = default;
    };
}

#endif // ALICE_IVIEW_H