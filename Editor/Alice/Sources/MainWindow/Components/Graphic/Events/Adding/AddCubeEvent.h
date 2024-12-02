#ifndef ALICE_ADD_CUBE_EVENT_H
#define ALICE_ADD_CUBE_EVENT_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events::Adding
{
    class AddCubeEvent : public wxEvent
    {
    public:
        AddCubeEvent();

        wxEvent *Clone() const override;
    };

    wxDECLARE_EVENT(ADD_CUBE_EVENT_TYPE, AddCubeEvent);

    typedef void (wxEvtHandler::*AddCubeEventFunction)(AddCubeEvent &);
    #define AddCubeEventHandler(func) wxEVENT_HANDLER_CAST(AddCubeEventFunction, func)  

    #define EVT_ADD_CUBE(func) wx__DECLARE_EVT1(ADD_CUBE_EVENT_TYPE, wxID_ANY, AddCubeEventHandler(func))
}

#endif // ALICE_ADD_CUBE_EVENT_H