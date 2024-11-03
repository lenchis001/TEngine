#ifndef ALICE_SAVE_SCENE_EVENT_H
#define ALICE_SAVE_SCENE_EVENT_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events
{
    class SaveSceneEvent : public wxEvent
    {
    public:
        SaveSceneEvent();

        wxEvent *Clone() const override;
    };

    wxDECLARE_EVENT(SAVE_SCENE_EVENT_TYPE, SaveSceneEvent);

    typedef void (wxEvtHandler::*SaveSceneEventFunction)(SaveSceneEvent &);
#define SaveSceneEventHandler(func) wxEVENT_HANDLER_CAST(SaveSceneEventFunction, func)

#define EVT_SAVE_SCENE(func) wx__DECLARE_EVT1(SAVE_SCENE_EVENT_TYPE, wxID_ANY, SaveSceneEventFunction(func))
}

#endif // ALICE_SAVE_SCENE_EVENT_H