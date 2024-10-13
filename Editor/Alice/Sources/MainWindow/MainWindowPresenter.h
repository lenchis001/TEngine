#ifndef ALICE_MAINWINDOWPRESENTER_H
#define ALICE_MAINWINDOWPRESENTER_H

#include "IMainWindowPresenter.h"

namespace Alice::MainWindow
{
    class MainWindowPresenter : public IMainWindowPresenter
    {
    public:
        void injectView(IMainWindowView* view);

    private:
        IMainWindowView* _view;
    };
}

#endif // ALICE_MAINWINDOWPRESENTER_H