#include <wx/wx.h>
#include "Core/IoC/Container.h"

#include "MainWindow/MainWindowPresenter.h"
#include "MainWindow/MainWindowView.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    auto container = std::make_shared<Alice::Core::IoC::Container>();

    container->registerType<Alice::MainWindow::MainWindowPresenter>([&](Alice::Core::IoC::Container *container)
                                                 { return new Alice::MainWindow::MainWindowPresenter(); });

    container->registerType<Alice::MainWindow::MainWindowView>([&](Alice::Core::IoC::Container *container)
                                            {
        auto presenter = std::shared_ptr<Alice::MainWindow::MainWindowPresenter>(container->resolve<Alice::MainWindow::MainWindowPresenter>());

        auto view = new Alice::MainWindow::MainWindowView(presenter);
        presenter->injectView(view);

        return view; });

    container->resolve<Alice::MainWindow::MainWindowView>()->Show(true);

    return true;
}