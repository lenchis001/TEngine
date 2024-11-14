#include "ISceneTreePresenter.h"

namespace Alice::MainWindow::Children::Scene::Tree
{
    class SceneTreePresenter : public ISceneTreePresenter
    {
    public:
        void injectView(ISceneTreeView *view) override;

        void selectSceneItem(int id) override;

    private:
        ISceneTreeView *_view;
    };
}