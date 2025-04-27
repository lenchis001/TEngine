#include "GraphicsServiceBase.h"

#include "Components/Graphics/PlatformWrapping/GlWrapper.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics;

using namespace TEngine::Components::Graphics::CameraTracking;

GraphicsServiceBase::GraphicsServiceBase(
	std::shared_ptr<ISceneService> sceneService,
	std::shared_ptr<IGuiService> guiService,
	std::shared_ptr<IMeshLoadingService> meshLoadingService,
	std::shared_ptr<ITexturesService> texturesService)
	: _sceneService(sceneService),
	  _guiService(guiService),
	  _meshLoadingService(meshLoadingService),
	  _texturesService(texturesService)
{
}

GraphicsServiceBase::~GraphicsServiceBase()
{
}

void GraphicsServiceBase::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
#if defined(_WIN32)
	InitializeOpenGLFunctionPointers();
#endif

	_meshLoadingService->initialize();
	_texturesService->initialize();
	_sceneService->initialize(parameters->getSceneParameters());
	_guiService->initialize();

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsServiceBase::deinitialize()
{
	_sceneService->deinitialize();
}

std::shared_ptr<ISceneService> GraphicsServiceBase::getSceneService()
{
	return _sceneService;
}

std::shared_ptr<IGuiService> GraphicsServiceBase::getGuiService()
{
	return _guiService;
}

void GraphicsServiceBase::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sceneService->render(getTime());
	_guiService->render();
}

void GraphicsServiceBase::resize(int width, int height)
{
	glViewport(0, 0, width, height);

	auto sceneService = this->getSceneService();
	auto activeCamera = sceneService->getActiveCamera();

	if (activeCamera)
	{
		activeCamera->setWindowSize(Vector2di(width, height));
	}
}