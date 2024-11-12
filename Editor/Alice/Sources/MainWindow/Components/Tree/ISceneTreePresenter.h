#ifndef ALICE_ISCENETREEPRESENTER_H
#define ALICE_ISCENETREEPRESENTER_H

#include "Core/IPresenter.h"

#include "ISceneTreeView.h"

namespace Alice::MainWindow::Components::Tree
{
    class ISceneTreePresenter : public Core::IPresenter<ISceneTreeView>
    {
    public:
        virtual void selectSceneItem(int id) = 0;
    };
}

#endif // ALICE_ISCENETREEPRESENTER_H