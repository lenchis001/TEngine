#include "GL/glew.h"

#include "GraphicsServiceBase.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics::Services;

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
	_meshLoadingService->initialize();
	_texturesService->initialize();
	_sceneService->initialize();
	_guiService->initialize();

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
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