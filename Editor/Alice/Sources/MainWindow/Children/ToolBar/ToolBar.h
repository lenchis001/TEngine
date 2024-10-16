#ifndef ALICE_MAINTOOLBAR_H
#define ALICE_MAINTOOLBAR_H

#include "IToolBar.h"

namespace Alice::MainWindow::Children::ToolBar
{
    class ToolBar : public IToolBar
    {
    public:
        ToolBar(wxWindow *parent);
    };
}

#endif // ALICE_MAINTOOLBAR_H