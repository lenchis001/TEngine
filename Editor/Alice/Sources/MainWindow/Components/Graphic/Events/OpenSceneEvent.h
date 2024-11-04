#ifndef ALICE_OPEN_SCENE_EVENT_H
#define ALICE_OPEN_SCENE_EVENT_H

#include <string>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events
{
    class OpenSceneEvent : public wxEvent
    {
    public:
        OpenSceneEvent(const std::string& path);

        wxEvent *Clone() const override;

        const std::string& getPath() const;

    private:
        std::string _path;
    };

    wxDECLARE_EVENT(OPEN_SCENE_EVENT_TYPE, OpenSceneEvent);

    typedef void (wxEvtHandler::*OpenSceneEventFunction)(OpenSceneEvent &);
#define OpenSceneEventHandler(func) wxEVENT_HANDLER_CAST(OpenSceneEventFunction, func)

#define EVT_OPEN_SCENE(func) wx__DECLARE_EVT1(OPEN_SCENE_EVENT_TYPE, wxID_ANY, OpenSceneEventFunction(func))
}

#endif // ALICE_OPEN_SCENE_EVENT_H