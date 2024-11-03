#ifndef SAVE_SCENE_DIALOG_MIXIN_H
#define SAVE_SCENE_DIALOG_MIXIN_H

#include <string>

namespace Alice::MainWindow::Components::Graphic::Mixins
{
    class SaveSceneDialogMixin
    {
    protected:
        std::string showSaveSceneDialog();
    };
}

#endif // SAVE_SCENE_DIALOG_MIXIN_H