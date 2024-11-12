#ifndef ALICE_MAINWINDOWVIEW_H
#define ALICE_MAINWINDOWVIEW_H

#include "IMainWindowView.h"

#include <memory>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "IMainWindowPresenter.h"

#include "Core/CustomParent/CustomParentBuilder.h"

#include "Components/Graphic/IGraphicContext.h"
#include "Components/Tree/ISceneTreeView.h"

#include "Children/MainMenu/IMainMenuView.h"
#include "Children/ToolBar/IToolBar.h"

using namespace Alice::MainWindow::Components::Graphic;
using namespace Alice::MainWindow::Components::Tree;
using namespace Alice::MainWindow::Children::MainMenu;
using namespace Alice::Core::CustomParent;

namespace Alice::MainWindow
{
    class MainWindowView : public wxFrame, public IMainWindowView
    {
    public:
        MainWindowView(
            std::shared_ptr<MainWindow::IMainWindowPresenter> presenter,
            IMainMenuView* mainMenu,
            std::shared_ptr<CustomParentBuilder<ISceneTreeView>> sceneTreeBuilder);

    private:
        void _createMainMenu();
        void _createMainArea(wxSizer* windowSizer);
        void _createWorkArea(wxSizer* windowSizer, std::shared_ptr<CustomParentBuilder<ISceneTreeView>> sceneTreeBuilder);

        // Main menu
        Children::MainMenu::IMainMenuView* _mainMenu;

        // Main area
        std::shared_ptr<Children::ToolBar::IToolBar> _toolBar;
        
        //Work area
        std::shared_ptr<wxPanel> _workArea;
        std::shared_ptr<IGraphicContext> _graphicContext;
        std::shared_ptr<ISceneTreeView> _sceneTree;

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // ALICE_MAINWINDOWVIEW_H