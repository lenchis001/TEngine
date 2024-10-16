#ifndef ALICE_ISCENETREEVIEW_H
#define ALICE_ISCENETREEVIEW_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/treectrl.h"

namespace Alice::MainWindow::Components::Tree
{
    class ISceneTree : public wxTreeCtrl
    {
    public:
        ISceneTree(wxWindow *parent) : wxTreeCtrl(parent) {}
    };
}

#endif // ALICE_ISCENETREEVIEW_H