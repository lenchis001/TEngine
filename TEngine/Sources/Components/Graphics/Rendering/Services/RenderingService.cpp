#include "GL/glew.h"

#include "stdexcept"

#include "RenderingService.h"

#include "CameraStrategies/CameraStrategyBase.h"
#include "CameraStrategies/FpsCameraStrategy.h"
#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "RenderingStrategies/RenderingStrategyBase.h"
#include "RenderingStrategies/RenderingOptimizationDecorator.h"
#include "RenderingStrategies/Meshes/MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes;

RenderingService::RenderingService(
	std::shared_ptr<IEventService> eventService,
	std::shared_ptr<IShadersService> shadersService,
	std::shared_ptr<IBuffersService> bufferCacheService,
	std::shared_ptr<ITexturesService> textureService,
	std::shared_ptr<IMeshService> meshService)
	: _window(nullptr),
	  _eventService(eventService),
	  _shadersService(shadersService),
	  _bufferCacheService(bufferCacheService),
	  _textureService(textureService),
	  _meshService(meshService),
	  _activeCamera(nullptr),
	  _root(std::make_shared<RenderingStrategyBase>())
{
}

RenderingService::~RenderingService()
{
	glfwSetWindowSizeCallback(_window, nullptr);
	glfwTerminate();
}

void RenderingService::initialize(std::shared_ptr<IRenderingParameters> parameters)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, parameters->getOpenGlMajorVersion());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, parameters->getOpenGlMinorVersion());
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(parameters->getWidth(), parameters->getHeight(), parameters->getTitle().c_str(), NULL, NULL);
	if (_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to open GLFW window");
	}

	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}

	setContext(this);
	glfwSetWindowSizeCallback(_window, &RenderingService::_onWindowResized);
	glfwSwapInterval(parameters->getIsVerticalSyncEnabled());

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}

bool RenderingService::isShutdownRequested() const
{
	return glfwWindowShouldClose(_window) != 0;
}

double RenderingService::getTime() const
{
	return glfwGetTime();
}

void RenderingService::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (_activeCamera)
	{
		_activeCamera->render();

		_root->render(_activeCamera);
	}

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

std::shared_ptr<IRenderingStrategy> RenderingService::addToRendering(
	PrimitiveTypes type,
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto cubeRenderingStrategy = std::make_shared<CubeRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		texturePath);

	(parent ? parent : _root)->addChild(cubeRenderingStrategy);

	return std::make_shared<RenderingOptimizationDecorator>(cubeRenderingStrategy);
}

std::shared_ptr<IRenderingStrategy> RenderingService::addMeshToRendering(
	std::string meshPath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto meshRenderingStrategy = std::make_shared<MeshRenderingStrategy>(_meshService, meshPath);

	(parent ? parent : _root)->addChild(meshRenderingStrategy);

	return std::make_shared<RenderingOptimizationDecorator>(meshRenderingStrategy);
}

std::shared_ptr<ICameraStrategy> RenderingService::setActiveCamera(BuildinCameraTypes cameraType)
{
	switch (cameraType)
	{
	case BuildinCameraTypes::BASE:
		_activeCamera = std::make_shared<CameraStrategyBase>(45.0f, 4.f / 3.f, 0.1f, 100.f, Vector3df(4, 3, 3), Vector3df(0, 0, 0));
		break;
	case BuildinCameraTypes::FPS:
		_activeCamera = std::make_shared<FpsCameraStrategy>(_eventService, 45.0f, 4.f / 3.f, 0.1f, 100.f, Vector3df(4, 3, 3));
		break;
	default:
		_activeCamera = nullptr;
		break;
	}

	return _activeCamera;
}

void RenderingService::setActiveCamera(std::shared_ptr<ICameraStrategy> camera)
{
	_activeCamera = camera;
}

void RenderingService::_onWindowResized(GLFWwindow *window, int width, int height)
{
#if (defined(_WIN32) || defined(_WIN64))
	glViewport(0, 0, width, height);
#endif

	auto that = getContext();

	if (that->_activeCamera)
	{
		that->_activeCamera->setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	}
}