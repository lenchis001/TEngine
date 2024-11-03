#ifndef ALICE_SAVE_SCENE_AS_EVENT_H
#define ALICE_SAVE_SCENE_AS_EVENT_H

#include <string>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events
{
    class SaveSceneAsEvent : public wxEvent
    {
    public:
        SaveSceneAsEvent(const std::string& path);

        wxEvent *Clone() const override;

        const std::string& getPath() const;

    private:
        std::string _path;
    };

    wxDECLARE_EVENT(SAVE_SCENE_AS_EVENT_TYPE, SaveSceneAsEvent);

    typedef void (wxEvtHandler::*SaveSceneAsEventFunction)(SaveSceneAsEvent &);
#define SaveSceneAsEventHandler(func) wxEVENT_HANDLER_CAST(SaveSceneAsEventFunction, func)

#define EVT_SAVE_SCENE_AS(func) wx__DECLARE_EVT1(SAVE_SCENE_AS_EVENT_TYPE, wxID_ANY, SaveSceneAsEventFunction(func))
}

#endif // ALICE_SAVE_SCENE_AS_EVENT_H