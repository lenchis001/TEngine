#include "IGraphicContext.h"

#include <memory>
#include <thread>

#include "IEngine.h"

#include "Core/Thread/FunctionConveyer.h"
#include "Events/CreateSceneEvent.h"
#include "Events/SaveSceneEvent.h"
#include "Events/SaveSceneAsEvent.h"
#include "Events/OpenSceneEvent.h"
#include "Events/Adding/AddMeshEvent.h"
#include "Events/Adding/AddCubeEvent.h"
#include "Mixins/SceneFileDialogMixin.h"
#include "Core/EventPropogationMixin.h"

using namespace TEngine;
using namespace TEngine::Components::Events::Models;

using namespace Alice::Core;
using namespace Alice::Core::Thread;
using namespace Alice::MainWindow::Components::Graphic::Events;
using namespace Alice::MainWindow::Components::Graphic::Events::Adding;
using namespace Alice::MainWindow::Components::Graphic::Mixins;

namespace Alice::MainWindow::Components::Graphic
{
    class GraphicContext : public FunctionConveyer, public SceneFileDialogMixin, public EventPropogationMixin, public IGraphicContext
    {
    public:
        GraphicContext(wxWindow *parent);
        ~GraphicContext();

    private:
        void _onResize(wxSizeEvent &event);
        void _onCreateScene(CreateSceneEvent& event);
        void _onSaveScene(SaveSceneEvent& event);
        void _onSaveSceneAs(SaveSceneAsEvent& event);
        void _onOpenScene(OpenSceneEvent& event);

        void _onAddMesh(AddMeshEvent& event);
        void _onAddCube(AddCubeEvent& event);

        void _onMouseMove(wxMouseEvent& event);
        void _onMouseButton(wxMouseEvent& event);
        void _onKey(wxKeyEvent& event);

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