#include "MainMenuView.h"

using namespace Alice::MainWindow::Children::MainMenu;

#define ADD_MESH_ID wxID_HIGHEST + 1
#define ADD_CUBE ADD_MESH_ID + 1

MainMenuView::MainMenuView(std::shared_ptr<IMainMenuPresenter> presenter) : _presenter(presenter)
{
    // File
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "New\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "Open\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "Save\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "Save As\tCtrl+Shift+S");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
    Append(fileMenu, "&File");

    // Edit
    wxMenu *editMenu = new wxMenu();
    editMenu->Append(wxID_UNDO, "Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "Redo\tCtrl+Y");
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, "Cut\tCtrl+X");
    editMenu->Append(wxID_COPY, "Copy\tCtrl+C");
    editMenu->Append(wxID_PASTE, "Paste\tCtrl+V");

    editMenu->AppendSeparator();

    // Add to scene
    wxMenu *addToSceneMenu = new wxMenu();
    addToSceneMenu->Append(ADD_MESH_ID, "Add mesh\tCtrl+Shift+M");
    addToSceneMenu->Append(ADD_CUBE, "Add cube\tCtrl+Shift+B");
    addToSceneMenu->Append(wxID_ANY, "Add solidbox\tCtrl+Shift+S");
    addToSceneMenu->Append(wxID_ANY, "Add skybox\tCtrl+Shift+K");

    editMenu->AppendSubMenu(addToSceneMenu, "Add to scene\tInsert");
    //

    Append(editMenu, "&Edit");

    // View
    wxMenu *viewMenu = new wxMenu();
    viewMenu->Append(wxID_ZOOM_IN, "Zoom In\tCtrl+Plus");
    viewMenu->Append(wxID_ZOOM_OUT, "Zoom Out\tCtrl+Minus");
    viewMenu->Append(wxID_ZOOM_100, "Zoom 100%\tCtrl+0");
    Append(viewMenu, "&View");

    // Help
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "About");
    Append(helpMenu, "&Help");
}

void MainMenuView::_onQuit(wxCommandEvent &event)
{
    _presenter->createScene();
}

void MainMenuView::_onSave(wxCommandEvent &event)
{
    _presenter->saveScene();
}

void MainMenuView::_onSaveAs(wxCommandEvent &event)
{
    _presenter->saveSceneAs();
}

void MainMenuView::_onOpen(wxCommandEvent &event)
{
    _presenter->openScene();
}

void MainMenuView::_onAddMesh(wxCommandEvent &event)
{
    _presenter->addMesh();
}

void MainMenuView::_onAddCube(wxCommandEvent &event)
{
    _presenter->addCube();
}

wxBEGIN_EVENT_TABLE(MainMenuView, wxMenuBar)
    EVT_MENU(wxID_NEW, MainMenuView::_onQuit)
        EVT_MENU(wxID_SAVE, MainMenuView::_onSave)
            EVT_MENU(wxID_SAVEAS, MainMenuView::_onSaveAs)
                EVT_MENU(wxID_OPEN, MainMenuView::_onOpen)
                    EVT_MENU(ADD_MESH_ID, MainMenuView::_onAddMesh)
                        EVT_MENU(ADD_CUBE, MainMenuView::_onAddCube)
                            wxEND_EVENT_TABLE()