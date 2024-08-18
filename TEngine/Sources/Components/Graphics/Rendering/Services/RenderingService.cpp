#include "GL/glew.h"

#include "stdexcept"

#include "RenderingService.h"

#include "Components/Graphics/Rendering/Models/RenderableObjects/RenderableObjectBase.h"
#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "CameraStrategies/CameraStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

RenderingService::RenderingService(std::shared_ptr<IShadersService> shadersService)
	: _window(nullptr),
	  _shadersService(shadersService),
	  _activeCamera(nullptr),
	  _root(std::make_shared<RenderableObjectBase>())
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

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(parameters->getIsVerticalSyncEnabled());

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
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

		for (const auto &strategy : _strategies)
		{
			strategy->render(vpMatrix);
		}
	}

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

std::shared_ptr<IRenderableObject> RenderingService::addToRendering(PrimitiveTypes type, std::shared_ptr<IRenderableObject> parent)
{
	auto primitive = std::make_shared<RenderableObjectBase>();
	(parent ? parent : _root)->addChild(primitive);

	_strategies.push_back(std::make_shared<CubeRenderingStrategy>(primitive, _shadersService));

	return primitive;
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