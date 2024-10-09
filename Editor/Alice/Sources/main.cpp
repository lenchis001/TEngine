#include <wx/wx.h>
#include "Core/IoC/Container.h"

#include "MainWindow/MainWindowPresenter.h"
#include "MainWindow/MainWindowView.h"

using namespace Alice::MainWindow;

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;

private:
    std::shared_ptr<MainWindowView> _view;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    auto container = std::make_shared<Alice::Core::IoC::Container>();

    container->registerType<MainWindowPresenter>([&](Alice::Core::IoC::Container *container)
                                                 { return std::make_shared<MainWindowPresenter>(); });

    container->registerType<MainWindowView>([&](Alice::Core::IoC::Container *container)
                                            {
        auto presenter = container->resolve<MainWindowPresenter>();

        auto view = std::make_shared<MainWindowView>(presenter);
        presenter->injectView(view);

        return view; });

    _view = container->resolve<MainWindowView>();
    _view->Show(true);

    return true;
}