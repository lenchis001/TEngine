#include "MainMenuPresenter.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "MainWindow/Components/Graphic/Events/CreateSceneEvent.h"
#include "MainWindow/Components/Graphic/Events/SaveSceneEvent.h"
#include "MainWindow/Components/Graphic/Events/SaveSceneAsEvent.h"
#include "MainWindow/Components/Graphic/Events/OpenSceneEvent.h"
#include "MainWindow/Components/Graphic/Events/Adding/AddMeshEvent.h"
#include "MainWindow/Components/Graphic/Events/Adding/AddCubeEvent.h"

using namespace Alice::MainWindow::Children::MainMenu;
using namespace Alice::MainWindow::Components::Graphic::Events;
using namespace Alice::MainWindow::Components::Graphic::Events::Adding;

void MainMenuPresenter::createScene()
{
    CreateSceneEvent event;

    postEventToChildren(event);
}

void MainMenuPresenter::saveScene()
{
    SaveSceneEvent event;

    postEventToChildren(event);
}

void MainMenuPresenter::saveSceneAs()
{
    auto location = showSaveSceneDialog();

    if (!location.empty())
    {
        SaveSceneAsEvent event(location);

        postEventToChildren(event);
    }
}

void MainMenuPresenter::openScene() {
    auto location = showOpenSceneDialog();

    if (!location.empty())
    {
        OpenSceneEvent event(location);

        postEventToChildren(event);
    }
}

void MainMenuPresenter::addMesh()
{
    auto result = wxFileSelector("Choose a mesh file to open...", wxEmptyString, wxEmptyString, wxEmptyString, "Wavefront OBJ (*.obj)|*.obj");

    if (!result.empty())
    {
        AddMeshEvent event(result);

        postEventToChildren(event);
    }
}

void MainMenuPresenter::addCube()
{
    AddCubeEvent event;

    postEventToChildren(event);
}

void MainMenuPresenter::injectView(IMainMenuView *view)
{
    _view = view;
}