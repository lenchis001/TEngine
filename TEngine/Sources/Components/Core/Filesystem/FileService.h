#include "IFileService.h"

namespace TEngine::Components::Core::Filesystem
{
    class FileService : public IFileService
    {
    public:
        std::string readAsString(const std::string &path) override;

        std::vector<uint8_t> readAsBytes(const std::string &path) override;

        std::string toAbsolutePath(const std::string &path) const override;
    protected:
        static std::string _removePrefix(const std::string &path, const std::string &prefix);
    };
}