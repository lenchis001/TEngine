#include "MainWindowPresenter.h"

using namespace Alice::MainWindow;

void MainWindowPresenter::injectView(std::weak_ptr<IMainWindowView> view)
{
    _view = view;
}