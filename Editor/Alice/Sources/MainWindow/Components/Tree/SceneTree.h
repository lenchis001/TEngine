#ifndef ALICE_SCENETREEVIEW_H
#define ALICE_SCENETREEVIEW_H

#include "ISceneTree.h"

#include "MainWindow/Components/Graphic/Events/SceneTree/UpdateSceneTreeEvent.h"

using namespace Alice::MainWindow::Components::Graphic::Events::SceneTree;

namespace Alice::MainWindow::Components::Tree
{
    class SceneTree : public ISceneTree
    {
    public:
        SceneTree(wxWindow *parent);

    private:
        void OnUpdateSceneTree(UpdateSceneTreeEvent &event);

        wxTreeItemId toTreeItem(const SceneTreeItem &sceneItem, const wxTreeItemId &root);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // ALICE_SCENETREEVIEW_H