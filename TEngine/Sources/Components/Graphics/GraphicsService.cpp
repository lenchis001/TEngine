#include "GL/glew.h"

#include "GraphicsService.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include "GLFW/glfw3native.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics::Services;

using namespace TEngine::Components::Graphics::CameraTracking;

GraphicsService::GraphicsService(
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

GraphicsService::~GraphicsService()
{
	glfwSetWindowSizeCallback(_window, nullptr);
	glfwTerminate();
}

void GraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
	_initializeGlfw(parameters);
	
	_meshLoadingService->initialize();
	_texturesService->initialize();
	_sceneService->initialize();
	_guiService->initialize();
}

void GraphicsService::deinitialize()
{
	_sceneService->deinitialize();
}

bool GraphicsService::isShutdownRequested() const
{
	return glfwWindowShouldClose(_window) != 0;
}

double GraphicsService::getTime() const
{
	return glfwGetTime();
}

std::shared_ptr<ISceneService> GraphicsService::getSceneService()
{
	return _sceneService;
}

std::shared_ptr<IGuiService> GraphicsService::getGuiService()
{
	return _guiService;
}

#ifdef _WIN32
HWND GraphicsService::getWindowHandler()
{
	return glfwGetWin32Window(_window);
}
#endif

void GraphicsService::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sceneService->render(getTime());
	_guiService->render();

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void GraphicsService::_initializeGlfw(std::shared_ptr<IGraphicsParameters> parameters)
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

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

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
	glfwSetWindowSizeCallback(_window, &GraphicsService::_onWindowResized);
	glfwSwapInterval(parameters->getIsVerticalSyncEnabled());

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}

void GraphicsService::_onWindowResized(GLFWwindow *window, int width, int height)
{
	#if (defined(_WIN32) || defined(_WIN64))
	glViewport(0, 0, width, height);
#endif

	auto that = getContext();
	auto sceneService = that->getSceneService();
	auto activeCamera = sceneService->getActiveCamera();

	if (activeCamera)
	{
		activeCamera->setWindowSize(Vector2di(width, height));
	}
}