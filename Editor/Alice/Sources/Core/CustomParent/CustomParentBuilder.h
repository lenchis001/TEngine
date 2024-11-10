#ifndef ALICE_CUSTOM_PARENT_BUILDER_H
#define ALICE_CUSTOM_PARENT_BUILDER_H

#include <functional>
#include <memory>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::Core::CustomParent
{
    template <class VT>
    class CustomParentBuilder
    {
    public:
        CustomParentBuilder(std::function<std::shared_ptr<VT>(wxWindow *parent)> builder)
            : _builder(builder)
        {
        }

        std::shared_ptr<VT> build(wxWindow *parent)
        {
            return _builder(parent);
        }

    private:
        std::function<std::shared_ptr<VT>(wxWindow *parent)> _builder;
    };
}

#endif // ALICE_CUSTOM_PARENT_BUILDER_H