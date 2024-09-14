#ifndef TENGINE_IREADER_H
#define TENGINE_IREADER_H

#include <string>

#include "AL/al.h"

namespace TEngine::Components::Audio::Services::Readers
{
    class IReader
    {
    public:
        virtual ~IReader() = default;

        virtual bool read(const std::string &path, ALuint source) = 0;
    };
}

#endif // TENGINE_IREADER_H