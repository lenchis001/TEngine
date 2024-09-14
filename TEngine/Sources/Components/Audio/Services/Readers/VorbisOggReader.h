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

        bool read(const std::string &path, ALuint source) override;

    private:
        void _readOggBlock(ALuint bufferId, std::size_t size, std::shared_ptr<OggVorbis_File> vorbisFile);

        static std::size_t ReadOgg(void* ptr, size_t size, size_t nmemb, void* datasource);
        static int SeekOgg(void* datasource, ogg_int64_t offset, int whence);
        static int CloseOgg(void* datasource);
        static long TellOgg(void* datasource);

        std::map<ALuint, SoundInfo> _buffers;
    };
}

#endif // TENGINE_VORBISOGGREADER_H