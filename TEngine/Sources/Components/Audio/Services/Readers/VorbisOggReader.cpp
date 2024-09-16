#include "VorbisOggReader.h"

#include <fstream>
#include <memory>
#include <cassert>

#include "Components/Audio/Services/AlMacroses.h"

#define NUM_OF_DYNBUF 2
#define DYNBUF_SIZE 10240

using namespace TEngine::Components::Audio::Services::Readers;

VorbisOggReader::~VorbisOggReader()
{
    assert(_buffers.empty() && "Buffers were not deleted properly");
}

bool VorbisOggReader::take(const std::string &path, ALuint sourceId)
{
    bool Streamed = false;

    int i, DynBuffs = 1;
    ogg_int64_t BlockSize;
    // OAL specific
    SoundInfo buffer;
    ALuint BufID = 0;
    // OggVorbis specific structures
    ov_callbacks cb;

    // Fill cb struct
    cb.close_func = &VorbisOggReader::_closeOgg;
    cb.read_func = &VorbisOggReader::_readOgg;
    cb.seek_func = &VorbisOggReader::_seekOgg;
    cb.tell_func = &VorbisOggReader::_tellOgg;

    // Create OggVorbis_File struct
    auto vorbisFile = std::make_shared<OggVorbis_File>();

    std::ifstream oggFilestream;

    // Open Ogg file
    oggFilestream.open(path.c_str(), std::ios_base::in | std::ios_base::binary);

    // Generate local buffers
    if (ov_open_callbacks(&oggFilestream, vorbisFile.get(), NULL, -1, cb) < 0)
    {
        // This is not ogg bitstream. Return
        return false;
    }

    // Check for existance of sound
    if (Streamed)
    {
        BlockSize = DYNBUF_SIZE;
        DynBuffs = NUM_OF_DYNBUF;
    }
    else
    {
        auto targetIterator = _buffers.find(path);

        if (targetIterator != _buffers.end())
        {
            BufID = targetIterator->second.ID;
        }

        BlockSize = ov_pcm_total(vorbisFile.get(), -1) * 4;
    }

    auto mInfo = ov_info(vorbisFile.get(), -1);

    // Fill buffer infos
    buffer.Rate = mInfo->rate;
    buffer.Format = (mInfo->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    buffer.usingCount = 1;

    // Fill buffers with data each block by DYNBUF_SIZE bytes
    if (Streamed || !BufID)
    {
        for (i = 0; i < DynBuffs; i++)
        {
            // Create buffers
            alGenBuffers(1, &buffer.ID);
            if (CHECK_ERROR())
                return false;
            _buffers.insert(
                std::pair<std::string, SoundInfo>(path, buffer));
            // Read amount (DYNBUF_SIZE) data into each buffer
            _readOggBlock(buffer, static_cast<std::size_t>(BlockSize), vorbisFile);
            if (CHECK_ERROR())
                return false;

            if (Streamed) // Place buffer to queue
            {
                alSourceQueueBuffers(sourceId, 1, &buffer.ID);
                if (CHECK_ERROR())
                    return false;
            }
            else
                alSourcei(sourceId, AL_BUFFER, buffer.ID);
        }
    }
    else
    {
        auto targetIterator = _buffers.find(path);
        targetIterator->second.usingCount++;

        alSourcei(sourceId, AL_BUFFER, targetIterator->second.ID);
    }

    oggFilestream.close();

    return true;
}

void VorbisOggReader::release(const std::string &path)
{
    auto targetIterator = _buffers.find(path);

    assert(targetIterator != _buffers.end() && "Buffer not found");

    if (targetIterator->second.usingCount > 1)
    {
        targetIterator->second.usingCount--;
    }
    else
    {
        alDeleteBuffers(1, &targetIterator->second.ID);
        _buffers.erase(targetIterator);
    }
}

void VorbisOggReader::_readOggBlock(const SoundInfo &soundInfo, std::size_t size, std::shared_ptr<OggVorbis_File> vorbisFile)
{
    char eof = 0;
    int current_section;
    long ret;
    char *PCM;

    size_t TotalRet = 0;

    if (size < 1)
        return;

    PCM = new char[size];

    // Read loop
    while (TotalRet < size)
    {
        ret = ov_read(vorbisFile.get(), PCM + TotalRet, size - TotalRet, 0, 2, 1,
                      &current_section);

        // if end of file or read limit exceeded
        if (ret == 0)
            break;
        else if (ret < 0) // Error in bitstream
        {
            //
        }
        else
        {
            TotalRet += ret;
        }
    }

    if (TotalRet > 0)
    {
        alBufferData(soundInfo.ID, soundInfo.Format, (void *)PCM, TotalRet,
                     soundInfo.Rate);
    }

    delete[] PCM;
}

std::size_t VorbisOggReader::_readOgg(void *ptr, size_t size, size_t nmemb, void *datasource)
{
    std::ifstream *file = static_cast<std::ifstream *>(datasource);
    file->read(static_cast<char *>(ptr), size * nmemb);
    return file->gcount();
}

int VorbisOggReader::_seekOgg(void *datasource, ogg_int64_t offset, int whence)
{
    std::ifstream *file = static_cast<std::ifstream *>(datasource);
    std::ios_base::seekdir dir;
    switch (whence)
    {
    case SEEK_SET:
        dir = std::ios_base::beg;
        break;
    case SEEK_CUR:
        dir = std::ios_base::cur;
        break;
    case SEEK_END:
        dir = std::ios_base::end;
        break;
    default:
        return -1;
    }
    file->seekg(offset, dir);
    return file->good() ? 0 : -1;
}

int VorbisOggReader::_closeOgg(void *datasource)
{
    std::ifstream *file = static_cast<std::ifstream *>(datasource);
    file->close();
    return 0;
}

long VorbisOggReader::_tellOgg(void *datasource)
{
    std::ifstream *file = static_cast<std::ifstream *>(datasource);
    return file->tellg();
}