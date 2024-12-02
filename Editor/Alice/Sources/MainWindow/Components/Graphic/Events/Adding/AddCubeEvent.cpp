#include "AddCubeEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events::Adding
{
    // this is a definition so can't be in a header
    wxDEFINE_EVENT(ADD_CUBE_EVENT_TYPE, AddCubeEvent);

    AddCubeEvent::AddCubeEvent()
        : wxEvent(wxID_ANY, ADD_CUBE_EVENT_TYPE)
    {
    }

    wxEvent *AddCubeEvent::Clone() const
    {
        return new AddCubeEvent();
    }
}