#ifndef TENGINE_SNDINFO_H
#define TENGINE_SNDINFO_H

#include <string>

namespace TEngine::Components::Audio::Models
{
    struct SoundInfo
    {
        unsigned int ID;
        std::string Filename;
        unsigned int Rate;
        unsigned int Format;
    };
}

#endif // TENGINE_SNDINFO_H