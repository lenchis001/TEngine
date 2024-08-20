#pragma once

#include "string"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define DYNAMIC_LIB_HANDLE HMODULE
#define LOAD_DYNAMIC_LIB(lib) LoadLibraryA(lib)
#define GET_DYNAMIC_FUNC(lib, func) reinterpret_cast<void*>(GetProcAddress(lib, func))
#define CLOSE_DYNAMIC_LIB FreeLibrary
#else
#include <dlfcn.h>
#define DYNAMIC_LIB_HANDLE void *
#define LOAD_DYNAMIC_LIB(lib) dlopen(lib, RTLD_LAZY)
#define GET_DYNAMIC_FUNC dlsym
#define CLOSE_DYNAMIC_LIB dlclose
#endif

namespace TEngine::Components::Graphics::ImageLoading::Services
{
    class PluginsLoadingAware
    {
    public:
        DYNAMIC_LIB_HANDLE loadPlugins(const std::string &path)
        {
            DYNAMIC_LIB_HANDLE lib = LOAD_DYNAMIC_LIB(path.c_str());
            if (!lib)
            {
                return nullptr;
            }

            return lib;
        }

        void *getFunction(DYNAMIC_LIB_HANDLE libHandle, const char *funcName)
        {
            void *funcPtr = GET_DYNAMIC_FUNC(libHandle, funcName);
            
            return funcPtr;
        }

        void closeLibrary(DYNAMIC_LIB_HANDLE libHandle)
        {
            if (libHandle)
            {
                CLOSE_DYNAMIC_LIB(libHandle);
            }
        }
    };
}