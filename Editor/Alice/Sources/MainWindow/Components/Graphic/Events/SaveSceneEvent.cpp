#include "SaveSceneEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events
{
    wxDEFINE_EVENT(SAVE_SCENE_EVENT_TYPE, SaveSceneEvent);

    SaveSceneEvent::SaveSceneEvent() : wxEvent(wxID_ANY, SAVE_SCENE_EVENT_TYPE)
    {
    }

    wxEvent *SaveSceneEvent::Clone() const
    {
        return new SaveSceneEvent();
    }
}