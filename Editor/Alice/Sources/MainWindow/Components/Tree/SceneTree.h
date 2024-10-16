#ifndef ALICE_SCENETREEVIEW_H
#define ALICE_SCENETREEVIEW_H

#include "ISceneTree.h"

namespace Alice::MainWindow::Components::Tree
{
    class SceneTree : public ISceneTree
    {
    public:
        SceneTree(wxWindow *parent);
    };
}

#endif // ALICE_SCENETREEVIEW_H