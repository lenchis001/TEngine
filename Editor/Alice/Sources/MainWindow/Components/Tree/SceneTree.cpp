#include "SceneTree.h"

using namespace Alice::MainWindow::Components::Tree;

SceneTree::SceneTree(wxWindow *parent)
    : ISceneTree(parent)
{
}

void SceneTree::OnUpdateSceneTree(UpdateSceneTreeEvent &event)
{
    DeleteAllItems();

    auto rootItem = event.getItem();

    wxTreeItemId root = AddRoot(rootItem.getName());

    for (auto &item : rootItem.getChildren())
    {
        toTreeItem(item, root);
    }

    Expand(root);
}

wxTreeItemId SceneTree::toTreeItem(const SceneTreeItem &sceneItem, const wxTreeItemId &root)
{
    auto currentItemName = sceneItem.getName();
    wxTreeItemId result = AppendItem(root, currentItemName);

    for (auto &childItem : sceneItem.getChildren())
    {
        auto child = toTreeItem(childItem, result);
    }

    return result;
}

wxBEGIN_EVENT_TABLE(SceneTree, ISceneTree)
    EVT_UPDATE_SCENE_TREE(SceneTree::OnUpdateSceneTree)
        wxEND_EVENT_TABLE()