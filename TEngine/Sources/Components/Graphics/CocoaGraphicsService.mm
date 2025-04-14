#ifdef __APPLE__

#include <chrono>
#include <thread>

#include <Cocoa/Cocoa.h>

#include "CocoaGraphicsService.h"

using namespace TEngine::Components::Graphics;

CocoaGraphicsService::CocoaGraphicsService(
    std::shared_ptr<ISceneService> sceneService,
    std::shared_ptr<IGuiService> guiService,
    std::shared_ptr<IMeshLoadingService> meshLoadingService,
    std::shared_ptr<ITexturesService> texturesService,
    void *parent)
    : GraphicsServiceBase(sceneService, guiService, meshLoadingService, texturesService),
      _parent(parent)
{
}

CocoaGraphicsService::~CocoaGraphicsService()
{
    [static_cast<NSOpenGLContext*>(_openGlContext) clearDrawable];
    [static_cast<NSOpenGLContext*>(_openGlContext) release];

    [static_cast<NSView*>(_openGlView) removeFromSuperview];
    [static_cast<NSView*>(_openGlView) release];
}

void CocoaGraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
    // Create the NSOpenGLPixelFormat
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize,32,
        NSOpenGLPFADepthSize,16,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFANoRecovery,
        0
    };
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];

    // Create the NSOpenGLContext
    _openGlContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

    [pixelFormat release];

    [static_cast<NSOpenGLContext*>(_openGlContext) makeCurrentContext];

    dispatch_async(dispatch_get_main_queue(), ^{
        NSView *parentView = static_cast<NSView*>(_parent);
        _openGlView = [[NSView alloc] initWithFrame:[parentView bounds]];

        [parentView addSubview:static_cast<NSView*>(_openGlView)];
        [static_cast<NSOpenGLContext*>(_openGlContext) setView:static_cast<NSView*>(_openGlView)];

        [static_cast<NSView*>(_openGlView) setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
    });

    // enable v-sync if requested
    if (parameters->getIsVerticalSyncEnabled())
    {
        GLint swapInterval = 1;
        [static_cast<NSOpenGLContext*>(_openGlContext) setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
    }

    GraphicsServiceBase::initialize(parameters);
}

void CocoaGraphicsService::deinitialize()
{
    GraphicsServiceBase::deinitialize();
}

bool CocoaGraphicsService::isShutdownRequested() const
{
    return false;
}

double CocoaGraphicsService::getTime() const
{
    return [[NSDate date] timeIntervalSince1970];
}

void CocoaGraphicsService::render()
{
    GraphicsServiceBase::render();

    // Swap the buffers
    [static_cast<NSOpenGLContext*>(_openGlContext) flushBuffer];
}

void CocoaGraphicsService::resize(int width, int height)
{
    GraphicsServiceBase::resize(width, height);

    [static_cast<NSOpenGLContext*>(_openGlContext) update];
}

#endif // __APPLE__