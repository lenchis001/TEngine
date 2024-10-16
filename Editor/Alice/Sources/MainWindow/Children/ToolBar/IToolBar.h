#ifndef ALICE_IMAINTOOLBAR_H
#define ALICE_IMAINTOOLBAR_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

namespace Alice::MainWindow::Children::ToolBar
{
    class IToolBar : public wxToolBar
    {
    public:
        IToolBar(wxWindow *parent) : wxToolBar(parent, wxID_ANY) {}

        virtual ~IToolBar() = default;
    };
}

#endif // ALICE_IMAINTOOLBAR_H