#include "UpdateSceneTreeEvent.h"

namespace Alice::MainWindow::Components::Graphic::Events::SceneTree
{
    wxDEFINE_EVENT(UPDATE_SCENE_TREE_EVENT_TYPE, UpdateSceneTreeEvent);

    UpdateSceneTreeEvent::UpdateSceneTreeEvent(const SceneTreeItem &item)
        : wxEvent(wxID_ANY, UPDATE_SCENE_TREE_EVENT_TYPE), _item(item)
    {
    }

    UpdateSceneTreeEvent::UpdateSceneTreeEvent() : UpdateSceneTreeEvent(SceneTreeItem(0, "root", {}))
    {
    }

    const SceneTreeItem &UpdateSceneTreeEvent::getItem() const
    {
        return _item;
    }

    wxEvent *UpdateSceneTreeEvent::Clone() const
    {
        return new UpdateSceneTreeEvent(getItem());
    }

    UpdateSceneTreeEvent UpdateSceneTreeEvent::fromRenderingStrategy(std::shared_ptr<IRenderingStrategy> renderingStrategy)
    {
        auto treeItem = toSceneTree(renderingStrategy);

        return UpdateSceneTreeEvent(treeItem);
    }

    SceneTreeItem UpdateSceneTreeEvent::toSceneTree(std::shared_ptr<IRenderingStrategy> renderingStrategy)
    {
        std::vector<SceneTreeItem> childItems;

        for (auto &childStrategy : renderingStrategy->getChildren())
        {
            childItems.push_back(toSceneTree(childStrategy));
        }

        return SceneTreeItem(0, renderingStrategy->getName(), childItems);
    }
}