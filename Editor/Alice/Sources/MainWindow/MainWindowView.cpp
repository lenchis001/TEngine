#include "MainWindowView.h"

#include "Components/Graphic/GraphicContext.h"

#include "Children/MainMenu/MainMenuView.h"
#include "Children/ToolBar/ToolBar.h"

using namespace Alice::MainWindow;
using namespace Alice::MainWindow::Children::ToolBar;

MainWindowView::MainWindowView(
    std::shared_ptr<MainWindow::IMainWindowPresenter> presenter,
    IMainMenuView *mainMenu,
    std::shared_ptr<CustomParentBuilder<ISceneTree>> sceneTreeBuilder)
    : wxFrame(nullptr, wxID_ANY, "Alice Editor"), _mainMenu(mainMenu), _sceneTree(nullptr)
{
    _createMainMenu();

    auto sizer = new wxBoxSizer(wxVERTICAL);

    _createMainArea(sizer);
    _createWorkArea(sizer, sceneTreeBuilder);

    this->SetSizer(sizer);
}

void MainWindowView::_createMainMenu()
{
    SetMenuBar(_mainMenu);
}

void MainWindowView::_createMainArea(wxSizer *windowSizer)
{
    _toolBar = std::make_shared<ToolBar>(this);
    windowSizer->Add(_toolBar.get(), 0, wxEXPAND);
}

void MainWindowView::_createWorkArea(wxSizer *windowSizer, std::shared_ptr<CustomParentBuilder<ISceneTree>> sceneTreeBuilder)
{
    _workArea = std::make_shared<wxPanel>(this, wxID_ANY);
    auto sizer = new wxBoxSizer(wxHORIZONTAL);

    _graphicContext = std::make_shared<GraphicContext>(_workArea.get());
    sizer->Add(_graphicContext.get(), 1, wxEXPAND | wxALL, 10);

    _sceneTree = sceneTreeBuilder->build(_workArea.get());
    _sceneTree->SetMinSize(wxSize(300, -1));
    _sceneTree->SetMaxSize(wxSize(300, -1));
    sizer->Add(_sceneTree.get(), 1, wxEXPAND | wxTOP | wxBOTTOM, 10);

    _workArea->SetSizer(sizer);

    windowSizer->Add(_workArea.get(), 1, wxEXPAND | wxTOP | wxBOTTOM, 10);
}

wxBEGIN_EVENT_TABLE(MainWindowView, wxFrame)
    wxEND_EVENT_TABLE()