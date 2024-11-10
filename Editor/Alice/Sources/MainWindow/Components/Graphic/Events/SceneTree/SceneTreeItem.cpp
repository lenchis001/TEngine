#include "SceneTreeItem.h"

using namespace Alice::MainWindow::Components::Graphic::Events::SceneTree;

SceneTreeItem::SceneTreeItem(int id, const std::string name, const std::vector<SceneTreeItem> children)
    : _id(id), _name(name), _children(children)
{
}

int SceneTreeItem::getId() const
{
    return _id;
}

const std::string& SceneTreeItem::getName() const
{
    return _name;
}

const std::vector<SceneTreeItem>& SceneTreeItem::getChildren() const
{
    return _children;
}