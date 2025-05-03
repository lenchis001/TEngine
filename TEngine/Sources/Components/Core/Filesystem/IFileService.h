#ifndef TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H
#define TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H

#include <string>
#include <vector>
#include <cstdint>

#define BUNDLE_PATH "bundle://"

namespace TEngine::Components::Core::Filesystem
{
    class IFileService
    {
    public:
        virtual std::string readAsString(const std::string &path) = 0;

        virtual std::vector<uint8_t> readAsBytes(const std::string &path) = 0;

        virtual std::string toAbsolutePath(const std::string &path) const = 0;
    };
}

#endif // TENGINE_COMPONENTS_CORE_FILESYSTEM_IFILESERVICE_H