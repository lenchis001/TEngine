#include "MainMenuView.h"

using namespace Alice::MainWindow::Children::MainMenu;

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

void MainMenuView::OnQuit(wxCommandEvent &event)
{
    _presenter->createScene();
}

void MainMenuView::OnSave(wxCommandEvent &event)
{
    _presenter->saveScene();
}

void MainMenuView::OnSaveAs(wxCommandEvent &event)
{
    _presenter->saveSceneAs();
}

void MainMenuView::OnOpen(wxCommandEvent &event)
{
    _presenter->openScene();
}

wxBEGIN_EVENT_TABLE(MainMenuView, wxMenuBar)
    EVT_MENU(wxID_NEW, MainMenuView::OnQuit)
        EVT_MENU(wxID_SAVE, MainMenuView::OnSave)
            EVT_MENU(wxID_SAVEAS, MainMenuView::OnSaveAs)
                EVT_MENU(wxID_OPEN, MainMenuView::OnOpen)
                    wxEND_EVENT_TABLE()