#ifndef ALICE_ISCENEMANAGEMENTVIEW_H
#define ALICE_ISCENEMANAGEMENTVIEW_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "IEngine.h"

namespace Alice::MainWindow::Children::Scene
{
    class ISceneManagementView : public wxPanel
    {
    public:
        ISceneManagementView(wxWindow *parent) : wxPanel(parent) {}

        virtual void hidePropertyGrid() = 0;

        virtual void showPropertyGrid(int id) = 0;
    };
}

#endif // ALICE_ISCENEMANAGEMENTVIEW_H