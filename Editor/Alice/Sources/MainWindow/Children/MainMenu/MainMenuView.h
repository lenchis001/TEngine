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

        void _onQuit(wxCommandEvent& event);

        void _onSave(wxCommandEvent& event);
        
        void _onSaveAs(wxCommandEvent& event);

        void _onOpen(wxCommandEvent& event);

        void _onAddMesh(wxCommandEvent& event);

        void _onAddCube(wxCommandEvent& event);

        std::shared_ptr<IMainMenuPresenter> _presenter;
    };
}