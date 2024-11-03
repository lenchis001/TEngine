#ifndef ALICE_IMAINWINDOWPRESENTER_H
#define ALICE_IMAINWINDOWPRESENTER_H

#include "Core/IPresenter.h"

namespace Alice::MainWindow
{
    class IMainWindowView;

    class IMainWindowPresenter : public Core::IPresenter<IMainWindowView>
    {
    public:
        virtual void injectView(IMainWindowView *view) = 0;
    };
}

#endif // ALICE_IMAINWINDOWPRESENTER_H