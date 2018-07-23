#include "RenderingService.h"

#include <GLFW/glfw3.h>

using namespace TEngine::Components::Graphics::Services::Rendering;

void RenderingService::render()
{
	glClear(GL_COLOR_BUFFER_BIT);



	glfwSwapBuffers(nullptr);
}
