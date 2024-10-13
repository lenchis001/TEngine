#include "GL/glew.h"

#include "GlfwGraphicsService.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics::Services;

using namespace TEngine::Components::Graphics::CameraTracking;

GlfwGraphicsService::GlfwGraphicsService(
	std::shared_ptr<ISceneService> sceneService,
	std::shared_ptr<IGuiService> guiService,
	std::shared_ptr<IMeshLoadingService> meshLoadingService,
	std::shared_ptr<ITexturesService> texturesService)
	: GraphicsServiceBase(sceneService, guiService, meshLoadingService, texturesService)
{
}

GlfwGraphicsService::~GlfwGraphicsService()
{
	glfwSetWindowSizeCallback(_window, nullptr);
	glfwTerminate();
}

void GlfwGraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
	_initializeGlfw(parameters);
	
	GlfwGraphicsService::initialize(parameters);
}

void GlfwGraphicsService::deinitialize()
{
	GraphicsServiceBase::deinitialize();
}

bool GlfwGraphicsService::isShutdownRequested() const
{
	return glfwWindowShouldClose(_window) != 0;
}

double GlfwGraphicsService::getTime() const
{
	return glfwGetTime();
}

void GlfwGraphicsService::render()
{
	GraphicsServiceBase::render();

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void GlfwGraphicsService::_initializeGlfw(std::shared_ptr<IGraphicsParameters> parameters)
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
	glfwSetWindowSizeCallback(_window, &GlfwGraphicsService::_onWindowResized);
	glfwSwapInterval(parameters->getIsVerticalSyncEnabled());

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}

void GlfwGraphicsService::_onWindowResized(GLFWwindow *window, int width, int height)
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