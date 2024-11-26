#ifndef ALICE_MAINMENUPRESENTER_H
#define ALICE_MAINMENUPRESENTER_H

#include "IMainMenuPresenter.h"

#include "Core/EventPropogationMixin.h"
#include "MainWindow/Components/Graphic/Mixins/SceneFileDialogMixin.h"

using namespace Alice::Core;
using namespace Alice::MainWindow::Components::Graphic::Mixins;

namespace Alice::MainWindow::Children::MainMenu
{
    class MainMenuPresenter : public IMainMenuPresenter, public EventPropogationMixin, public SceneFileDialogMixin
    {
    public:
        void createScene() override;

        void saveScene() override;

        void saveSceneAs() override;

        void openScene() override;

        void addMesh() override;

        void injectView(IMainMenuView *view) override;

    private:
        IMainMenuView *_view;
    };
}

#endif // ALICE_MAINMENUPRESENTER_H