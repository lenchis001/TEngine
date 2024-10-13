#include "MainWindowPresenter.h"

using namespace Alice::MainWindow;

void MainWindowPresenter::injectView(IMainWindowView* view)
{
    _view = view;
}