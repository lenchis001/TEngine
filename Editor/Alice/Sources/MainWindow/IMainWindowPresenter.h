#ifndef ALICE_IMAINWINDOWPRESENTER_H
#define ALICE_IMAINWINDOWPRESENTER_H

#include "Core/IPresenter.h"

namespace Alice::MainWindow
{
    class IMainWindowView;

    class IMainWindowPresenter : public Core::IPresenter<IMainWindowView>
    {
        
    };
}

#endif // ALICE_IMAINWINDOWPRESENTER_H