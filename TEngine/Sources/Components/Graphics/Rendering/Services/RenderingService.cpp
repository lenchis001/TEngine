#include "GL/glew.h"

#include "stdexcept"

#include "RenderingService.h"

#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "CameraStrategies/CameraStrategyBase.h"
#include "Components/Graphics/Rendering/Services/RenderingStrategies/RenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

RenderingService::RenderingService(
	std::shared_ptr<IShadersService> shadersService,
	std::shared_ptr<IBuffersService> bufferCacheService,
	std::shared_ptr<ITexturesService> textureService)
	: _window(nullptr),
	  _shadersService(shadersService),
	  _bufferCacheService(bufferCacheService),
	  _textureService(textureService),
	  _activeCamera(nullptr),
	  _root(std::make_shared<RenderingStrategyBase>())
{
}

RenderingService::~RenderingService()
{
	glfwSetWindowSizeCallback(_window, nullptr);
	glfwSetWindowUserPointer(_window, nullptr);
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

	glfwSetWindowUserPointer(_window, this);
	glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height)
							  {
		auto service = static_cast<RenderingService *>(glfwGetWindowUserPointer(window));
		service->_onWindowResized(width, height); });
	glfwSwapInterval(parameters->getIsVerticalSyncEnabled());

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	auto bigWorldParameters = parameters->getBigWorldParameters();
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
		const auto &vpMatrix = _activeCamera->getVpMatrix();
		const auto &viewArea = _activeCamera->getViewArea();

		_root->render(vpMatrix, viewArea);
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

	return cubeRenderingStrategy;
}

std::shared_ptr<ICameraStrategy> RenderingService::setActiveCamera(BuildinCameraTypes cameraType)
{
	switch (cameraType)
	{
	case BuildinCameraTypes::BASE:
		_activeCamera = std::make_shared<CameraStrategyBase>(45.0f, 4.f / 3.f, 0.1f, 100.f, Vector3df(4, 3, 3), Vector3df(0, 0, 0));
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

void RenderingService::_onWindowResized(int width, int height)
{
#if (defined(_WIN32) || defined(_WIN64))
	glViewport(0, 0, width, height);
#endif

	if (_activeCamera)
	{
		_activeCamera->setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	}
}