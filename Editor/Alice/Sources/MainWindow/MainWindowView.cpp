#include "MainWindowView.h"

#include "Components/GraphicContext.h"
#include "Components/Tree/SceneTree.h"

#include "Children/MainMenu/MainMenuView.h"
#include "Children/ToolBar/ToolBar.h"

using namespace Alice::MainWindow;
using namespace Alice::MainWindow::Children::MainMenu;
using namespace Alice::MainWindow::Components;
using namespace Alice::MainWindow::Components::Tree;
using namespace Alice::MainWindow::Children::ToolBar;

MainWindowView::MainWindowView(std::shared_ptr<MainWindow::IMainWindowPresenter> presenter)
    : wxFrame(nullptr, wxID_ANY, "Alice Editor")
{
    _createMainMenu();
    _createWorkArea();
    _createMainArea();
}

void MainWindowView::_createMainMenu()
{
    _mainMenuView = std::make_shared<MainMenuView>();
    SetMenuBar(_mainMenuView.get());
}

void MainWindowView::_createMainArea()
{
    _toolBar = std::make_shared<ToolBar>(this);

    auto sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(_toolBar.get(), 0, wxEXPAND);
    sizer->Add(_workArea.get(), 1, wxEXPAND | wxTOP | wxBOTTOM, 10);

    this->SetSizer(sizer);
}

void MainWindowView::_createWorkArea()
{
    _workArea = std::make_shared<wxPanel>(this, wxID_ANY);
    auto sizer = new wxBoxSizer(wxHORIZONTAL);

    _graphicContext = std::make_shared<GraphicContext>(_workArea.get());
    sizer->Add(_graphicContext.get(), 1, wxEXPAND | wxALL, 10);

    _sceneTree = std::make_shared<SceneTree>(_workArea.get());
    _sceneTree->SetMinSize(wxSize(300, -1));
    _sceneTree->SetMaxSize(wxSize(300, -1));
    sizer->Add(_sceneTree.get(), 1, wxEXPAND | wxTOP | wxBOTTOM, 10);

    _workArea->SetSizer(sizer);
}

wxBEGIN_EVENT_TABLE(MainWindowView, wxFrame)
    wxEND_EVENT_TABLE()