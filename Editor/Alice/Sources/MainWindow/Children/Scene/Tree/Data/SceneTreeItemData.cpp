#include "SceneTreeItemData.h"

using namespace Alice::MainWindow::Children::Scene::Tree::Data;

SceneTreeItemData::SceneTreeItemData(int id) : _id(id) {}

int SceneTreeItemData::getId() const
{
    return _id;
}