#include "SceneManagementView.h"

using namespace Alice::MainWindow::Children::Scene;

SceneManagementView::SceneManagementView(wxWindow *parent, std::shared_ptr<CustomParentBuilder<ISceneTreeView>> sceneTreeBuilder)
    : ISceneManagementView(parent)
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    _sceneTree = sceneTreeBuilder->build(this);
    sizer->Add(_sceneTree.get(), 1, wxEXPAND | wxALL, 0);

    SetSizer(sizer);
}

void SceneManagementView::hidePropertyGrid()
{
}

void SceneManagementView::showPropertyGrid(int id)
{
}

wxBEGIN_EVENT_TABLE(SceneManagementView, ISceneManagementView)

wxEND_EVENT_TABLE()