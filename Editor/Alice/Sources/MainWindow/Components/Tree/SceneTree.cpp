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

    for (auto &item : event.getItem().getChildren())
    {
        toTreeItem(item, root);
    }

    Expand(root);
}

wxTreeItemId SceneTree::toTreeItem(const SceneTreeItem &sceneItem, const wxTreeItemId &root)
{
    wxTreeItemId result = AppendItem(root, sceneItem.getName());

    for (auto &childItem : sceneItem.getChildren())
    {
        auto child = toTreeItem(childItem, result);
        AppendItem(child, childItem.getName());
    }

    return result;
}

wxBEGIN_EVENT_TABLE(SceneTree, ISceneTree)
    EVT_UPDATE_SCENE_TREE(SceneTree::OnUpdateSceneTree)
        wxEND_EVENT_TABLE()