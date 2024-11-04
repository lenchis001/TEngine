#include "IMainMenuView.h"

#include <memory>

#include "IMainMenuPresenter.h"

namespace Alice::MainWindow::Children::MainMenu
{
    class MainMenuView : public IMainMenuView
    {
    public:
        MainMenuView(std::shared_ptr<IMainMenuPresenter> presenter);

        virtual ~MainMenuView() = default;
    private:
        wxDECLARE_EVENT_TABLE();

        void OnQuit(wxCommandEvent& event);

        void OnSave(wxCommandEvent& event);
        
        void OnSaveAs(wxCommandEvent& event);

        void OnOpen(wxCommandEvent& event);

        std::shared_ptr<IMainMenuPresenter> _presenter;
    };
}