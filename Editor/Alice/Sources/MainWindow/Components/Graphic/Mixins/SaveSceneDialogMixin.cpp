#include "SaveSceneDialogMixin.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

using namespace Alice::MainWindow::Components::Graphic::Mixins;

std::string SaveSceneDialogMixin::showSaveSceneDialog() {
    return wxSaveFileSelector("scene", "TEngine Scene (*.tscene)|*.tscene");
}