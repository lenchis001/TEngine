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
#include "Components/Tree/ISceneTree.h"

#include "Children/MainMenu/IMainMenuView.h"
#include "Children/ToolBar/IToolBar.h"

namespace Alice::MainWindow
{
    class MainWindowView : public wxFrame, public IMainWindowView
    {
    public:
        MainWindowView(std::shared_ptr<MainWindow::IMainWindowPresenter> presenter);

    private:
        void _createMainMenu();
        void _createMainArea();
        void _createWorkArea();

        // Main menu
        Children::MainMenu::IMainMenuView* _mainMenu;

        // Main area
        std::shared_ptr<Children::ToolBar::IToolBar> _toolBar;
        
        //Work area
        std::shared_ptr<wxPanel> _workArea;
        std::shared_ptr<Components::IGraphicContext> _graphicContext;
        std::shared_ptr<Components::Tree::ISceneTree> _sceneTree;

        std::shared_ptr<Children::MainMenu::IMainMenuView> _mainMenuView;

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // ALICE_MAINWINDOWVIEW_H