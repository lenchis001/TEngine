
#ifndef ALICE_ADD_MESH_EVENT_H
#define ALICE_ADD_MESH_EVENT_H

#include <string>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Components::Graphic::Events::Adding
{
    class AddMeshEvent : public wxEvent
    {
    public:
        AddMeshEvent(const std::string& path);

        const std::string& getPath() const;

        wxEvent *Clone() const override;

    private:
        std::string _path;
    };

    wxDECLARE_EVENT(ADD_MESH_EVENT_TYPE, AddMeshEvent);

    typedef void (wxEvtHandler::*AddMeshEventFunction)(AddMeshEvent &);
    #define AddMeshEventHandler(func) wxEVENT_HANDLER_CAST(AddMeshEventFunction, func)  

    #define EVT_ADD_MESH(func) wx__DECLARE_EVT1(ADD_MESH_EVENT_TYPE, wxID_ANY, AddMeshEventHandler(func))
}

#endif // ALICE_ADD_MESH_EVENT_H