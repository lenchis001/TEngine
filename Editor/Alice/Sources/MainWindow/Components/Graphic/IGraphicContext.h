
#ifndef ALICE_MAINWINDOW_COMPONENTS_IGRAPHICCONTEXT_H
#define ALICE_MAINWINDOW_COMPONENTS_IGRAPHICCONTEXT_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <IEngine.h>

namespace Alice::MainWindow::Components::Graphic
{
    class IGraphicContext : public wxPanel
    {
    public:
        IGraphicContext(wxWindow* parent) : wxPanel(parent) {}

        virtual ~IGraphicContext() = default;
    };
}

#endif // ALICE_MAINWINDOW_COMPONENTS_IGRAPHICCONTEXT_H