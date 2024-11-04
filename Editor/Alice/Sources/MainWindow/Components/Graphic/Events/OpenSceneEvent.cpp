#include "OpenSceneEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events
{
    // this is a definition so can't be in a header
    wxDEFINE_EVENT(OPEN_SCENE_EVENT_TYPE, OpenSceneEvent);

    OpenSceneEvent::OpenSceneEvent(const std::string& path) : wxEvent(wxID_ANY, OPEN_SCENE_EVENT_TYPE),
                                                           _path(path)
    {
    }

    wxEvent *OpenSceneEvent::Clone() const
    {
        return new OpenSceneEvent(_path);
    }

    const std::string& OpenSceneEvent::getPath() const {
        return _path;
    }
}