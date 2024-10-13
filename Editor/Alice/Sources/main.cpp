#include <wx/wx.h>
#include "Core/IoC/Container.h"

#include "MainWindow/MainWindowPresenter.h"
#include "MainWindow/MainWindowView.h"

#include "MainWindow/Children/MainMenu/MainMenuView.h"

using namespace Alice::MainWindow;

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

    container->registerType<MainMenuView>([&](Alice::Core::IoC::Container *container)
                                          { return new MainMenuView(); });

    container->registerType<MainWindowPresenter>([&](Alice::Core::IoC::Container *container)
                                                 { return new MainWindowPresenter(); });

    container->registerType<MainWindowView>([&](Alice::Core::IoC::Container *container)
                                            {
        auto presenter = std::shared_ptr<MainWindowPresenter>(container->resolve<MainWindowPresenter>());
        auto mainMenuView = container->resolve<MainMenuView>();

        auto view = new MainWindowView(presenter, mainMenuView);
        presenter->injectView(view);

        return view; });

    container->resolve<MainWindowView>()->Show(true);

    return true;
}