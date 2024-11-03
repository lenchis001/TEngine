#include "SaveSceneAsEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events
{
    // this is a definition so can't be in a header
    wxDEFINE_EVENT(SAVE_SCENE_AS_EVENT_TYPE, SaveSceneAsEvent);

    SaveSceneAsEvent::SaveSceneAsEvent(const std::string& path) : wxEvent(wxID_ANY, SAVE_SCENE_AS_EVENT_TYPE),
                                                           _path(path)
    {
    }

    wxEvent *SaveSceneAsEvent::Clone() const
    {
        return new SaveSceneAsEvent(_path);
    }

    const std::string& SaveSceneAsEvent::getPath() const {
        return _path;
    }
}