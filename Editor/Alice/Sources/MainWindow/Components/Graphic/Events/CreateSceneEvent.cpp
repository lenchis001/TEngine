#include "CreateSceneEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events
{
    // this is a definition so can't be in a header
    wxDEFINE_EVENT(CREATE_SCENE_EVENT_TYPE, CreateSceneEvent);

    CreateSceneEvent::CreateSceneEvent() : wxEvent(wxID_ANY, CREATE_SCENE_EVENT_TYPE)
    {
    }

    wxEvent *CreateSceneEvent::Clone() const
    {
        return new CreateSceneEvent();
    }

}