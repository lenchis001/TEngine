#include <jni.h>

#include "AndroidOut.h"
#include "Renderer.h"

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include "IEngine.h"

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

using namespace TEngine;
using namespace TEngine::Components::Graphics;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Scene;

std::shared_ptr<IEngine> engine;
std::shared_ptr<IGraphicsService> graphicsService;

void setupScene(std::shared_ptr<ISceneService> sceneService)
{
    auto camera = sceneService->setActiveCamera(BuildinCameraTypes::FPS);
    camera->setWindowSize({2037,1080});

    //sceneService->addSkyCude();

    auto solid = sceneService->addSolidbox();
    solid->setPosition(Vector3df(5.0f, -10.0f, 0.0f));
    solid->setRotation(Vector3df(.0f, .0f, .1f));
    solid->setScale(Vector3df(35.0f, 1.0f, 15.0f));
    solid->setIsVisualizationEnabled(true);

    /*for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            auto cube = sceneService->addMesh("./DemoResources/test plane/plane.obj");
            cube->setPosition(Vector3df(2.0f * i, 0.0f, 2.0f * j));
        }

        if (i > 5)
        {
            auto cube = sceneService->addCube("./DemoResources/texture2.bmp", nullptr, PhysicsFlags::STATIC);
            cube->setPosition(Vector3df(i, 0.0f, 0.0f));
        }

        auto cube2 = sceneService->addCube("./DemoResources/texture2.bmp", nullptr, PhysicsFlags::DYNAMIC);
        cube2->setPosition(Vector3df(i, 2.f * i, 0.0f));

        auto testCube = sceneService->addMesh("./DemoResources/test cube/cube.obj");
        testCube->setPosition(Vector3df(0.0f, 0.0f, 3.0f * i));

        auto sofa = sceneService->addMesh("./DemoResources/sofa.obj");
        sofa->setPosition(Vector3df(0.f, 0.f, -3.0f * i - 5.0f));
    }*/
}

/*!
 * Handles commands sent to this Android application
 * @param pApp the app the commands are coming from
 * @param cmd the command to handle
 */
void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW: {
            // A new window is created, associate a renderer with it. You may replace this with a
            // "game" class if that suits your needs. Remember to change all instances of userData
            // if you change the class here as a reinterpret_cast is dangerous this in the
            // android_main function and the APP_CMD_TERM_WINDOW handler case.
            engine = createEngine(pApp);

            auto creationParameters = TEngine::Models::createEngineParameters();

            auto graphicsParameters = creationParameters->getGraphicsParameters();
            graphicsParameters->setTitle("AndroidDemo");
            graphicsParameters->setIsVerticalSyncEnabled(true);
            graphicsParameters->getSceneParameters()->setSequenceUpdateThreshold(20.f);

            engine->initialize(creationParameters);

            graphicsService = engine->getGraphicsService();

            setupScene(graphicsService->getSceneService());
            //pApp->userData = new Renderer(pApp);
            break;
        }
        case APP_CMD_TERM_WINDOW:
            // The window is being destroyed. Use this to clean up your userData to avoid leaking
            // resources.
            //
            // We have to check if userData is assigned just in case this comes in really quickly
            if (pApp->userData) {
                auto *pRenderer = reinterpret_cast<Renderer *>(pApp->userData);
                pApp->userData = nullptr;
                delete pRenderer;
            }
            break;
        default:
            break;
    }
}

/*!
 * Enable the motion events you want to handle; not handled events are
 * passed back to OS for further processing. For this example case,
 * only pointer and joystick devices are enabled.
 *
 * @param motionEvent the newly arrived GameActivityMotionEvent.
 * @return true if the event is from a pointer or joystick device,
 *         false for all other input devices.
 */
bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

/*!
 * This the main entry point for a native activity
 */
void android_main(struct android_app *pApp) {
    // Can be removed, useful to ensure your code is running
    aout << "Welcome to android_main" << std::endl;

    // Register an event handler for Android events
    pApp->onAppCmd = handle_cmd;

    // Set input event filters (set it to NULL if the app wants to process all inputs).
    // Note that for key inputs, this example uses the default default_key_filter()
    // implemented in android_native_app_glue.c.
    //android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    // This sets up a typical game/event loop. It will run until the app is destroyed.
    do {
        // Process all pending events before running game logic.
        bool done = false;
        while (!done) {
            // 0 is non-blocking.
            int timeout = 0;
            int events;
            android_poll_source *pSource;
            int result = ALooper_pollOnce(timeout, nullptr, &events,
                                          reinterpret_cast<void **>(&pSource));
            switch (result) {
                case ALOOPER_POLL_TIMEOUT:
                    [[clang::fallthrough]];
                case ALOOPER_POLL_WAKE:
                    // No events occurred before the timeout or explicit wake. Stop checking for events.
                    done = true;
                    break;
                case ALOOPER_EVENT_ERROR:
                    aout << "ALooper_pollOnce returned an error" << std::endl;
                    break;
                case ALOOPER_POLL_CALLBACK:
                    break;
                default:
                    if (pSource) {
                        pSource->process(pApp, pSource);
                    }
            }
        }

        // Check if any user data is associated. This is assigned in handle_cmd
        if (engine) {
            // We know that our user data is a Renderer, so reinterpret cast it. If you change your
            // user data remember to change it here
            //auto *pRenderer = reinterpret_cast<Renderer *>(pApp->userData);

            // Process game input
            //pRenderer->handleInput();

            // Render a frame
            //pRenderer->render();

            graphicsService->render();
        }
    } while (!pApp->destroyRequested);
}
}