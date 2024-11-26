#include "SceneFileDialogMixin.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

using namespace Alice::MainWindow::Components::Graphic::Mixins;

std::string SceneFileDialogMixin::showSaveSceneDialog() {
    return wxSaveFileSelector("scene", "TEngine Scene (*.tscene)|*.tscene");
}

std::string SceneFileDialogMixin::showOpenSceneDialog() {
    return wxFileSelector("Choose TEngine scene file to open...", wxEmptyString, wxEmptyString, wxEmptyString, "TEngine Scene (*.tscene)|*.tscene");
}