#include "SceneTreePresenter.h"

using namespace Alice::MainWindow::Children::Scene::Tree;

void SceneTreePresenter::injectView(ISceneTreeView *view)
{
    _view = view;
}

void SceneTreePresenter::selectSceneItem(int id)
{
}