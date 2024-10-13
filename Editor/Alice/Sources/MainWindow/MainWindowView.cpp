#include "MainWindowView.h"

#include "Components/GraphicContext.h"

using namespace Alice::MainWindow;

MainWindowView::MainWindowView(std::shared_ptr<MainWindow::IMainWindowPresenter> presenter, IMainMenuView* mainMenuView)
    : wxFrame(nullptr, wxID_ANY, "Alice Editor")
{
    SetMenuBar(mainMenuView);

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    auto display = new wxStaticText(panel, wxID_ANY, "0");
    wxButton* button = new wxButton(panel, wxID_ANY, "Update");
    sizer->Add(display, 0, wxALL | wxCENTER, 5);
    sizer->Add(button, 0, wxALL | wxCENTER, 5);

    _graphicContext = std::make_shared<GraphicContext>(panel);
    sizer->Add(_graphicContext.get(), 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(sizer);
}

wxBEGIN_EVENT_TABLE(MainWindowView, wxFrame)
wxEND_EVENT_TABLE()