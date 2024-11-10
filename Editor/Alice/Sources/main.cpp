#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Core/IoC/Container.h"

#include "MainWindow/MainWindowPresenter.h"
#include "MainWindow/MainWindowView.h"
#include "MainWindow/Children/MainMenu/MainMenuPresenter.h"
#include "MainWindow/Children/MainMenu/MainMenuView.h"
#include "MainWindow/Components/Tree/SceneTree.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(MyApp);

void registerDependencies(std::shared_ptr<Alice::Core::IoC::Container> container)
{
    // Main Menu
    container->registerType<Alice::MainWindow::Children::MainMenu::IMainMenuPresenter>(
        [&](Alice::Core::IoC::Container *container)
        {
            return new Alice::MainWindow::Children::MainMenu::MainMenuPresenter();
        });

    container->registerType<Alice::MainWindow::Children::MainMenu::IMainMenuView>(
        [&](Alice::Core::IoC::Container *container)
        {
            auto rawPresenter = container->resolve<Alice::MainWindow::Children::MainMenu::IMainMenuPresenter>();
            auto presenter = std::shared_ptr<Alice::MainWindow::Children::MainMenu::IMainMenuPresenter>(rawPresenter);

            auto view = new Alice::MainWindow::Children::MainMenu::MainMenuView(presenter);
            presenter->injectView(view);

            return view;
        });

    container->registerType<Alice::Core::CustomParent::CustomParentBuilder<Alice::MainWindow::Components::Tree::ISceneTree>>(
        [&](Alice::Core::IoC::Container *container)
        {
            return new Alice::Core::CustomParent::CustomParentBuilder<Alice::MainWindow::Components::Tree::ISceneTree>(
                [&](wxWindow *parent)
                {
                    return std::make_shared<Alice::MainWindow::Components::Tree::SceneTree>(parent);
                });
        });

    // Main Window
    container->registerType<Alice::MainWindow::IMainWindowPresenter>(
        [&](Alice::Core::IoC::Container *container)
        {
            return new Alice::MainWindow::MainWindowPresenter();
        });

    container->registerType<Alice::MainWindow::MainWindowView>(
        [&](Alice::Core::IoC::Container *container)
        {
            auto rawPresenter = container->resolve<Alice::MainWindow::IMainWindowPresenter>();
            auto presenter = std::shared_ptr<Alice::MainWindow::IMainWindowPresenter>(rawPresenter);

            auto rawMainMenu = container->resolve<Alice::MainWindow::Children::MainMenu::IMainMenuView>();

            auto rawSceneTreeBuilder = container->resolve<Alice::Core::CustomParent::CustomParentBuilder<Alice::MainWindow::Components::Tree::ISceneTree>>();
            auto sceneTreeBuilder = std::shared_ptr<Alice::Core::CustomParent::CustomParentBuilder<Alice::MainWindow::Components::Tree::ISceneTree>>(rawSceneTreeBuilder);

            auto view = new Alice::MainWindow::MainWindowView(presenter, rawMainMenu, sceneTreeBuilder);
            presenter->injectView(view);

            return view;
        });
}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    auto container = std::make_shared<Alice::Core::IoC::Container>();

    registerDependencies(container);

    container->resolve<Alice::MainWindow::MainWindowView>()->Show(true);

    return true;
}