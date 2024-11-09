#include "IGraphicContext.h"

#include <memory>
#include <thread>

#include "IEngine.h"

#include "Core/Thread/FunctionConveyer.h"
#include "Events/CreateSceneEvent.h"
#include "Events/SaveSceneEvent.h"
#include "Events/SaveSceneAsEvent.h"
#include "Events/OpenSceneEvent.h"
#include "Mixins/SceneFileDialogMixin.h"

using namespace TEngine;
using namespace TEngine::Components::Events::Models;

using namespace Alice::Core::Thread;
using namespace Alice::MainWindow::Components::Graphic::Events;
using namespace Alice::MainWindow::Components::Graphic::Mixins;

namespace Alice::MainWindow::Components::Graphic
{
    class GraphicContext : public FunctionConveyer, public SceneFileDialogMixin, public IGraphicContext
    {
    public:
        GraphicContext(wxWindow *parent);
        ~GraphicContext();

    private:
        void OnResize(wxSizeEvent &event);
        void OnCreateScene(CreateSceneEvent& event);
        void OnSaveScene(SaveSceneEvent& event);
        void OnSaveSceneAs(SaveSceneAsEvent& event);
        void OnOpenScene(OpenSceneEvent& event);

        void OnMouseMove(wxMouseEvent& event);
        void OnMouseButton(wxMouseEvent& event);
        void OnKey(wxKeyEvent& event);

        void _initializeEngine();

        static MouseButtons _toTEngineMouseButton(int wxButtonId);
        static KeyboardKeys _toTEngineKey(int wxKeyCode);

        std::thread _renderThread;

        std::shared_ptr<IEngine> _engine;
        bool _isShutdownRequested;

        std::string _currentScenePath;

        wxDECLARE_EVENT_TABLE();
    };
}