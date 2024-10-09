#ifndef ALICE_IMAINWINDOWVIEW_H
#define ALICE_IMAINWINDOWVIEW_H

#include "Core/IView.h"

#include "IMainWindowPresenter.h"

namespace Alice::MainWindow
{
    class IMainWindowView : public Core::IView<IMainWindowPresenter>
    {
    };
}

#endif // ALICE_IMAINWINDOWVIEW_H