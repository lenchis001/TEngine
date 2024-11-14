#include "ISceneManagementView.h"

#include <memory>

#include "Core/CustomParent/CustomParentBuilder.h"
#include "Tree/ISceneTreeView.h"

using namespace Alice::Core::CustomParent;
using namespace Alice::MainWindow::Children::Scene::Tree;

namespace Alice::MainWindow::Children::Scene
{
    class SceneManagementView : public ISceneManagementView
    {
    public:
        SceneManagementView(wxWindow *parent, std::shared_ptr<CustomParentBuilder<ISceneTreeView>> sceneTreeBuilder);

        void hidePropertyGrid() override;

        void showPropertyGrid(int id) override;

    private:
        std::shared_ptr<ISceneTreeView> _sceneTree;

        wxDECLARE_EVENT_TABLE();
    };
}