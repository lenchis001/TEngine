#ifndef ALICE_CREATE_SCENE_EVENT_H
#define ALICE_CREATE_SCENE_EVENT_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events
{
    class CreateSceneEvent : public wxEvent
    {
    public:
        CreateSceneEvent();

        wxEvent *Clone() const override;
    };

    wxDECLARE_EVENT(CREATE_SCENE_EVENT_TYPE, CreateSceneEvent);

    typedef void (wxEvtHandler::*CreateSceneEventFunction)(CreateSceneEvent &);
    #define CreateSceneEventHandler(func) wxEVENT_HANDLER_CAST(CreateSceneEventFunction, func)  

    #define EVT_CREATE_SCENE(func) wx__DECLARE_EVT1(CREATE_SCENE_EVENT_TYPE, wxID_ANY, CreateSceneEventHandler(func))
}

#endif // ALICE_CREATE_SCENE_EVENT_H