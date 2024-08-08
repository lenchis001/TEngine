#include "GL/glew.h"

#include "RenderingService.h"

using namespace TEngine::Components::Graphics::Services::Rendering;

RenderingService::RenderingService()
	: _window(nullptr)
{
}

void RenderingService::initialize(std::shared_ptr<IRenderingParameters> parameters)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		throw std::exception("Failed to initialize GLFW");
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
		throw std::exception("Failed to open GLFW window");
	}

	glfwMakeContextCurrent(_window);

	 if (glewInit() != GLEW_OK) {
		 throw std::exception("Failed to initialize GLEW");
	 }

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void RenderingService::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_window);
	glfwPollEvents();
}
