#ifndef ALICE_SCENETREEVIEW_H
#define ALICE_SCENETREEVIEW_H

#include "ISceneTreeView.h"

#include <memory>

#include "ISceneTreePresenter.h"

#include "MainWindow/Components/Graphic/Events/SceneTree/UpdateSceneTreeEvent.h"

using namespace Alice::MainWindow::Components::Graphic::Events::SceneTreeView;

namespace Alice::MainWindow::Components::Tree
{
    class SceneTreeView : public ISceneTreeView
    {
    public:
        SceneTreeView(wxWindow *parent, std::shared_ptr<ISceneTreePresenter> presenter);

    private:
        void OnUpdateSceneTree(UpdateSceneTreeEvent &event);
        void OnSelectionChanged(wxTreeEvent &event);

        wxTreeItemId toTreeItem(const SceneTreeItem &sceneItem, const wxTreeItemId &root);

        std::shared_ptr<ISceneTreePresenter> _presenter;

        wxDECLARE_EVENT_TABLE();
    };
}

#endif // ALICE_SCENETREEVIEW_H