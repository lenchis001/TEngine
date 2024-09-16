#ifndef TENGINE_SNDINFO_H
#define TENGINE_SNDINFO_H

#include <string>

#include "AL/al.h"

namespace TEngine::Components::Audio::Models
{
    struct SoundInfo
    {
        ALuint ID;
        ALuint Rate;
        ALuint Format;

        unsigned int usingCount;
    };
}

#endif // TENGINE_SNDINFO_H