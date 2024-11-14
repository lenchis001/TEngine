#ifndef ALICE_SCENETREEITEMDATA_H
#define ALICE_SCENETREEITEMDATA_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/treectrl.h"

namespace Alice::MainWindow::Children::Scene::Tree::Data
{
    class SceneTreeItemData : public wxTreeItemData
    {
    public:
        SceneTreeItemData(int id);

        int getId() const;

    private:
        int _id;
    };
}

#endif // ALICE_SCENETREEITEMDATA_H