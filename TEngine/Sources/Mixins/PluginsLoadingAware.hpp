#ifndef TENGINE_PLUGINSLOADINGAWARE_H
#define TENGINE_PLUGINSLOADINGAWARE_H

#include "vector"
#include "unordered_map"
#include "string"
#include "filesystem"

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

#define LOAD_FUNCTION_NAME "load"

namespace TEngine::Mixins
{
    template <class PT>
    class PluginsLoadingAware
    {
    public:
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
            std::vector<std::string> plugins = _findPlugins(directory);

            for (const auto &plugin : plugins)
            {
                std::shared_ptr<PT> loadedPlugin = _loadPlugin(plugin);
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

        std::vector<std::string> _findPlugins(std::string directory) const
        {
            std::vector<std::string> libraries;

            for (const auto &entry : std::filesystem::directory_iterator(directory))
            {
                std::string filename = entry.path().filename().string();
                if (filename.size() > 3 && (filename.substr(filename.size() - 3) == ".so" || filename.substr(filename.size() - 4) == ".dll" || filename.substr(filename.size() - 6) == ".dylib"))
                {
                    libraries.push_back(entry.path().string());
                }
            }

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
    };
}

#endif // TENGINE_PLUGINSLOADINGAWARE_H