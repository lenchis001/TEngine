#ifndef TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H
#define TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H

#include <string>

#define BUNDLE_PATH "bundle://"

namespace TEngine::Components::Core::Filesystem
{
    class IFileService
    {
    public:
        virtual std::string read(const std::string &path) = 0;
    };
}

#endif // TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H