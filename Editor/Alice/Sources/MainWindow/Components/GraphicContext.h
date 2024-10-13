#include "IGraphicContext.h"

#include <memory>
#include <thread>

#include "IEngine.h"

#include "Core/Thread/FunctionConveyer.h"

using namespace TEngine;

using namespace Alice::Core::Thread;

namespace Alice::MainWindow::Components
{
    class GraphicContext : public FunctionConveyer, public IGraphicContext
    {
    public:
        GraphicContext(wxWindow *parent);
        ~GraphicContext();

    private:
        void OnResize(wxSizeEvent &event);

        void _initializeEngine();

        std::thread _renderThread;

        std::shared_ptr<IEngine> _engine;
        bool _isShutdownRequested;

        wxDECLARE_EVENT_TABLE();
    };
}