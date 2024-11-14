#ifndef ALICE_MAINTOOLBAR_H
#define ALICE_MAINTOOLBAR_H

#include "IToolBar.h"

namespace Alice::MainWindow::Children::ToolBar
{
    class ToolBar : public IToolBar
    {
    public:
        ToolBar(wxWindow *parent);

        static wxBitmap _createColoredBitmap(const wxString &filePath, const wxSize &size, const wxColour &bgColor);
    };
}

#endif // ALICE_MAINTOOLBAR_H