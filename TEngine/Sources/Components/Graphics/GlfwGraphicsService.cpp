#include "GL/glew.h"

#include "GlfwGraphicsService.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics;

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
	
	GraphicsServiceBase::initialize(parameters);
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

	_window = glfwCreateWindow(parameters->getWidth(), parameters->getHeight(), parameters->getTitle().c_str(), NULL, NULL);
	if (_window == nullptr)
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
}

void GlfwGraphicsService::_onWindowResized(GLFWwindow *window, int width, int height)
{
	auto that = getContext();
	
	that->resize(width, height);
}