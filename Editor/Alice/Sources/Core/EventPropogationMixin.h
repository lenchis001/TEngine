#ifndef ALICE_EVENTPROPOGATION_MIXIN_H
#define ALICE_EVENTPROPOGATION_MIXIN_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::Core
{
    class EventPropogationMixin
    {
    protected:
        void postEventToChildren(wxEvent &event, wxWindow *parent = nullptr);
    };
}

#endif // ALICE_EVENTPROPOGATION_MIXIN_H