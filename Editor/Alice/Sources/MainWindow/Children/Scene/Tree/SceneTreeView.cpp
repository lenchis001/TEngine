#include "SceneTreeView.h"

#include "Data/SceneTreeItemData.h"

using namespace Alice::MainWindow::Children::Scene::Tree;
using namespace Alice::MainWindow::Children::Scene::Tree::Data;

SceneTreeView::SceneTreeView(wxWindow *parent, std::shared_ptr<ISceneTreePresenter> presenter)
    : ISceneTreeView(parent), _presenter(presenter)
{
}

void SceneTreeView::OnUpdateSceneTree(UpdateSceneTreeEvent &event)
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

void SceneTreeView::OnSelectionChanged(wxTreeEvent &event)
{
    auto item = dynamic_cast<SceneTreeItemData *>(GetItemData(event.GetItem()));

    if (item)
    {
        _presenter->selectSceneItem(item->getId());
    }
}

wxTreeItemId SceneTreeView::toTreeItem(const SceneTreeItem &sceneItem, const wxTreeItemId &root)
{
    auto currentItemName = sceneItem.getName();

    auto resultData = new SceneTreeItemData(sceneItem.getId());
    wxTreeItemId result = AppendItem(root, currentItemName, -1, -1, resultData);

    for (auto &childItem : sceneItem.getChildren())
    {
        auto child = toTreeItem(childItem, result);
    }

    return result;
}

wxBEGIN_EVENT_TABLE(SceneTreeView, ISceneTreeView)
    EVT_UPDATE_SCENE_TREE(SceneTreeView::OnUpdateSceneTree)
        EVT_TREE_SEL_CHANGED(wxID_ANY, SceneTreeView::OnSelectionChanged)
            wxEND_EVENT_TABLE()