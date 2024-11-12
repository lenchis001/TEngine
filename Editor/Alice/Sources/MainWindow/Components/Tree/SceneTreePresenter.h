#include "ISceneTreePresenter.h"

namespace Alice::MainWindow::Components::Tree
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