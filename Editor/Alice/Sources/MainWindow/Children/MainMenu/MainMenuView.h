#include "IMainMenuView.h"

namespace Alice::MainWindow::Children::MainMenu
{
    class MainMenuView : public IMainMenuView
    {
    public:
        MainMenuView();

        virtual ~MainMenuView() = default;
    };
}