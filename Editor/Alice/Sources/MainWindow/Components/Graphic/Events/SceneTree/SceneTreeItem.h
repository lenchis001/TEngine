#ifndef ALICE_SCENETREEITEM_H
#define ALICE_SCENETREEITEM_H

#include <vector>
#include <string>

namespace Alice::MainWindow::Components::Graphic::Events::SceneTree
{
    class SceneTreeItem
    {
    public:
        SceneTreeItem(int id, const std::string name, const std::vector<SceneTreeItem> children);

        int getId() const;

        const std::string &getName() const;

        const std::vector<SceneTreeItem> &getChildren() const;

    private:
        std::string _name;
        int _id;
        std::vector<SceneTreeItem> _children;
    };
}

#endif // ALICE_SCENETREEITEM_H