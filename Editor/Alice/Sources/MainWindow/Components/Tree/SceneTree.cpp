#include "SceneTree.h"

using namespace Alice::MainWindow::Components::Tree;

SceneTree::SceneTree(wxWindow *parent)
    : ISceneTree(parent)
{
    wxTreeItemId root = AddRoot("Scene");
    wxTreeItemId child1 = AppendItem(root, "Child 1");
    wxTreeItemId child2 = AppendItem(root, "Child 2");
    AppendItem(child1, "Child 1.1");
    AppendItem(child1, "Child 1.2");
    AppendItem(child2, "Child 2.1");
    AppendItem(child2, "Child 2.2");
    Expand(root);
}