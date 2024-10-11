#ifndef ALICE_MAINWINDOWVIEW_H
#define ALICE_MAINWINDOWVIEW_H

#include "IMainWindowView.h"

#include <memory>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "IMainWindowPresenter.h"

#include "Components/IGraphicContext.h"

#include "Children/MainMenu/IMainMenuView.h"

using namespace Alice::MainWindow::Components;
using namespace Alice::MainWindow::Children::MainMenu;

namespace Alice::MainWindow
{
    class MainWindowView : public wxFrame, public IMainWindowView
    {
    public:
        MainWindowView(std::shared_ptr<MainWindow::IMainWindowPresenter> presenter);

    private:
        std::shared_ptr<IGraphicContext> _graphicContext;

        std::shared_ptr<IMainMenuView> _mainMenuView;

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // ALICE_MAINWINDOWVIEW_H