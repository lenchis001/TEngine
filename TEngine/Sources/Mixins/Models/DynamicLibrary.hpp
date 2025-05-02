#ifndef TENGINE_DYNAMIC_LIBRARY_H
#define TENGINE_DYNAMIC_LIBRARY_H

#include <string>
#include <unistd.h> // Include for close
#include <exception>

namespace TEngine::Mixins::Models
{
    class DynamicLibrary
    {
    public:
#ifdef __ANDROID__
        DynamicLibrary(int fileDescriptor)
            : _fileDescriptor(fileDescriptor) {}
#else
        DynamicLibrary(const std::string &path)
                : _path(path) {}
#endif

        ~DynamicLibrary()
        {
#ifdef __ANDROID__
            close(_fileDescriptor);
#endif // __ANDROID__
        }

        std::string getPath() const
        {
#ifdef __ANDROID__
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "/proc/self/fd/%d", _fileDescriptor);

            char resolved[PATH_MAX];
            ssize_t len = readlink(path, resolved, sizeof(resolved) - 1);
            if (len == -1)
            {
                throw std::exception();
            }

            resolved[len] = '\0';
            return resolved;
#else
            return _path;
#endif
        }

    private:
#ifdef __ANDROID__
        int _fileDescriptor;
#else
        std::string _path;
#endif
    };
}

#endif // TENGINE_DYNAMIC_LIBRARY_H