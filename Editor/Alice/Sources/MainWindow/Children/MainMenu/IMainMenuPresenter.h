#ifndef ALICE_IMAINMENUPRESENTER_H
#define ALICE_IMAINMENUPRESENTER_H

#include <string>

#include "Core/IPresenter.h"

#include "IMainMenuView.h"

using namespace Alice::Core;

namespace Alice::MainWindow::Children::MainMenu
{
    class IMainMenuPresenter : public IPresenter<IMainMenuView>
    {
    public:
        virtual void createScene() = 0;

        virtual void saveScene() = 0;
        
        virtual void saveSceneAs() = 0;

        virtual void openScene() = 0;

        virtual void addMesh() = 0;
    };
}

#endif // ALICE_IMAINMENUPRESENTER_H