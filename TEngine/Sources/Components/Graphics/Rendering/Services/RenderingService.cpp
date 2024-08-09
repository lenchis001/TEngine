#include "GL/glew.h"

#include "RenderingService.h"

#include "Strategies/Primitives/CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Strategies::Primitives;

RenderingService::RenderingService(std::shared_ptr<IShadersService> shadersService)
	: _window(nullptr), _shadersService(shadersService)
{
}

void RenderingService::initialize(std::shared_ptr<IRenderingParameters> parameters)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
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

	 if (glewInit() != GLEW_OK) {
		 throw std::runtime_error("Failed to initialize GLEW");
	 }

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void RenderingService::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto strategy : _strategies)
	{
		strategy->render();
	}

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void RenderingService::addToRendering(std::shared_ptr<IRenderableObject> object, PrimitiveTypes type)
{
	_strategies.push_back(std::make_shared<CubeRenderingStrategy>(object, _shadersService));
}