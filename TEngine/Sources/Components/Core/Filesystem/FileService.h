#include "IFileService.h"

namespace TEngine::Components::Core::Filesystem
{
    class FileService : public IFileService
    {
    public:
        std::string read(const std::string &path) override;

    protected:
        static std::string _removePrefix(const std::string &path, const std::string &prefix);
    };
}