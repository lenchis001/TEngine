#ifndef SAVE_SCENE_DIALOG_MIXIN_H
#define SAVE_SCENE_DIALOG_MIXIN_H

#include <string>

namespace Alice::MainWindow::Components::Graphic::Mixins
{
    class SceneFileDialogMixin
    {
    protected:
        std::string showSaveSceneDialog();

        std::string showOpenSceneDialog();
    };
}

#endif // SAVE_SCENE_DIALOG_MIXIN_H