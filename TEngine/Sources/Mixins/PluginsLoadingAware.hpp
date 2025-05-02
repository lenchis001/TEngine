#ifndef TENGINE_PLUGINSLOADINGAWARE_H
#define TENGINE_PLUGINSLOADINGAWARE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>

#ifdef __ANDROID__
#include <dirent.h>   // Include for directory traversal on POSIX systems
#include <sys/stat.h> // Include for file status checks
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <unistd.h>
#include <sys/syscall.h>

#ifndef __NR_memfd_create
#if defined(__aarch64__)
#define __NR_memfd_create 279
#elif defined(__arm__)
#define __NR_memfd_create 385
#elif defined(__x86_64__)
#define __NR_memfd_create 319
#elif defined(__i386__)
#define __NR_memfd_create 356
#else
#error "Platform not supported"
#endif
#endif

#ifndef MFD_CLOEXEC
#define MFD_CLOEXEC 0x0001U
#endif

#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define DYNAMIC_LIB_HANDLE HMODULE
#define LOAD_DYNAMIC_LIB(lib) LoadLibraryA(lib)
#define GET_DYNAMIC_FUNC(lib, func) reinterpret_cast<void *>(GetProcAddress(lib, func))
#define CLOSE_DYNAMIC_LIB FreeLibrary
#else
#include <dlfcn.h>
#define DYNAMIC_LIB_HANDLE void *
#define LOAD_DYNAMIC_LIB(lib) dlopen(lib, RTLD_LAZY)
#define GET_DYNAMIC_FUNC dlsym
#define CLOSE_DYNAMIC_LIB dlclose
#endif

#include "Models/DynamicLibrary.hpp"

#define LOAD_FUNCTION_NAME "load"

using namespace TEngine::Mixins::Models;

namespace TEngine::Mixins
{
    template <class PT>
    class PluginsLoadingAware
    {
    public:
#ifdef __ANDROID__
        PluginsLoadingAware(AAssetManager *assetManager)
            : _assetManager(assetManager) {}
#endif

        ~PluginsLoadingAware()
        {
            for (const auto &lib : _loadedLibraries)
            {
                closeLibrary(lib);
            }
        }

    protected:
        void _initialize(std::string directory)
        {
            auto plugins = _findPlugins(directory);

            for (const auto &plugin : plugins)
            {
                std::shared_ptr<PT> loadedPlugin = _loadPlugin(plugin->getPath());
                if (loadedPlugin)
                {
                    for (const auto &extension : loadedPlugin->getSupportedExtensions())
                    {
                        _plugins[extension] = loadedPlugin;
                    }
                }
            }
        }

        std::shared_ptr<PT> _load(const std::string &path)
        {
            auto extension = path.substr(path.find_last_of('.') + 1);

            auto pluginIterator = _plugins.find(extension);

            if (pluginIterator == _plugins.end())
            {
                return nullptr;
            }

            return pluginIterator->second;
        }

    private:
        typedef std::shared_ptr<PT> (*loadPluginDelegate)();

        std::vector<std::shared_ptr<DynamicLibrary>> _findPlugins(std::string directory) const
        {
            std::vector<std::shared_ptr<DynamicLibrary>> libraries;

#ifdef __ANDROID__
            if (!_assetManager)
            {
                // Handle error if asset manager is unavailable
                return libraries;
            }

            auto finalDirectoryPath = "generated/" + directory;

            AAssetDir *assetDir = AAssetManager_openDir(_assetManager, finalDirectoryPath.c_str());
            if (!assetDir)
            {
                // Handle error if directory cannot be opened
                return libraries;
            }

            const char *filename = nullptr;
            while ((filename = AAssetDir_getNextFileName(assetDir)) != nullptr)
            {
                // Check for valid plugin extensions
                std::string filePath = finalDirectoryPath + "/" + filename;
                if (filePath.size() > 3 &&
                    (filePath.substr(filePath.size() - 3) == ".so" ||
                     filePath.substr(filePath.size() - 4) == ".dll" ||
                     filePath.substr(filePath.size() - 6) == ".dylib"))
                {
                    AAsset *asset = AAssetManager_open(_assetManager, filePath.c_str(), AASSET_MODE_STREAMING);
                    if (asset)
                    {
                        int memFd = syscall(__NR_memfd_create, filename, MFD_CLOEXEC);
                        if (memFd != -1)
                        {
                            char buffer[1024];
                            int bytesRead;
                            while ((bytesRead = AAsset_read(asset, buffer, sizeof(buffer))) > 0)
                            {
                                write(memFd, buffer, bytesRead);
                            }
                            lseek(memFd, 0, SEEK_SET); // Reset file descriptor position
                            libraries.push_back(std::make_shared<DynamicLibrary>(memFd));
                        }
                        AAsset_close(asset);
                    }
                }
            }

            AAssetDir_close(assetDir);
#else
            auto currentPath = std::filesystem::current_path();

            for (const auto &entry : std::filesystem::directory_iterator(currentPath.append(directory)))
            {
                std::string filename = entry.path().filename().string();
                if (filename.size() > 3 && (filename.substr(filename.size() - 3) == ".so" || filename.substr(filename.size() - 4) == ".dll" || filename.substr(filename.size() - 6) == ".dylib"))
                {
                    libraries.push_back(std::make_shared<DynamicLibrary>(entry.path().string()));
                }
            }
#endif

            return libraries;
        }

        std::shared_ptr<PT> _loadPlugin(const std::string &path)
        {
            auto lib = loadPlugins(path);

            auto function = getFunction(lib, LOAD_FUNCTION_NAME);
            auto delegate = reinterpret_cast<loadPluginDelegate>(function);

            auto plugin = delegate();
            return plugin;
        }

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

        std::unordered_map<std::string, std::shared_ptr<PT>> _plugins;
        std::vector<DYNAMIC_LIB_HANDLE> _loadedLibraries;

#ifdef __ANDROID__
        AAssetManager *_assetManager;
#endif
    };
}

#endif // TENGINE_PLUGINSLOADINGAWARE_H