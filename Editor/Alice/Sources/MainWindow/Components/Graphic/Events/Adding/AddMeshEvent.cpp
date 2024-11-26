#include "AddMeshEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events::Adding
{
    // this is a definition so can't be in a header
    wxDEFINE_EVENT(ADD_MESH_EVENT_TYPE, AddMeshEvent);

    AddMeshEvent::AddMeshEvent(const std::string &path)
        : wxEvent(wxID_ANY, ADD_MESH_EVENT_TYPE),
          _path(path)
    {
    }

    const std::string &AddMeshEvent::getPath() const
    {
        return _path;
    }

    wxEvent *AddMeshEvent::Clone() const
    {
        return new AddMeshEvent(_path);
    }

}