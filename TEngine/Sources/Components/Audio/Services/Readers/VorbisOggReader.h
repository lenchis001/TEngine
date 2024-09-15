#ifndef TENGINE_VORBISOGGREADER_H
#define TENGINE_VORBISOGGREADER_H

#include <cstddef>
#include <memory>
#include <map>

#include "vorbis/vorbisfile.h"

#include "IReader.h"
#include "Components/Audio/Models/SoundInfo.h"

using namespace TEngine::Components::Audio::Models;

namespace TEngine::Components::Audio::Services::Readers
{
    class VorbisOggReader : public IReader
    {
    public:
        ~VorbisOggReader();

        bool take(const std::string &path, ALuint source) override;

        void release(const std::string &path) override;

    private:
        void _readOggBlock(const SoundInfo &soundInfo, std::size_t size, std::shared_ptr<OggVorbis_File> vorbisFile);

        static std::size_t _readOgg(void *ptr, size_t size, size_t nmemb, void *datasource);
        static int _seekOgg(void *datasource, ogg_int64_t offset, int whence);
        static int _closeOgg(void *datasource);
        static long _tellOgg(void *datasource);

        std::map<std::string, SoundInfo> _buffers;
    };
}

#endif // TENGINE_VORBISOGGREADER_H