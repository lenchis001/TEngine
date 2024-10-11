#ifndef ALICE_IMAINMENUVIEW_H
#define ALICE_IMAINMENUVIEW_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Children::MainMenu
{
    class IMainMenuView : public wxMenuBar
    {
    public:
        IMainMenuView() : wxMenuBar() {}

        virtual ~IMainMenuView() = default;
    };
}

#endif // ALICE_IMAINMENUVIEW_H