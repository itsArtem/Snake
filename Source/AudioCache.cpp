#include "AudioCache.h"

#include <stdexcept>
#include <utility>

AudioCache::AudioCache(AudioCache &&audioCache) noexcept
	: chunks{std::move(audioCache.chunks)},
	music{std::move(audioCache.music)}
{
}

AudioCache::~AudioCache()
{
	clearChunks();
	clearMusic();
}

AudioCache &AudioCache::operator=(AudioCache &&audioCache) noexcept
{
	clearChunks();
	clearMusic();
	chunks = std::move(audioCache.chunks);
	music = std::move(audioCache.music);
	return *this;
}

void AudioCache::loadChunk(const std::string &path)
{
	Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
	if (!chunk) throw std::runtime_error{SDL_GetError()};
	chunks.emplace_back(chunk);
}

void AudioCache::loadMusic(const std::string &path)
{
	Mix_Music *music = Mix_LoadMUS(path.c_str());
	if (!music) throw std::runtime_error{SDL_GetError()};
	this->music.emplace_back(music);
}

void AudioCache::removeChunk(std::vector<Mix_Chunk>::size_type index) noexcept
{
	Mix_FreeChunk(chunks[index]);
	chunks.erase(chunks.begin() + index);
}

void AudioCache::removeMusic(std::vector<Mix_Music>::size_type index) noexcept
{
	Mix_FreeMusic(music[index]);
	music.erase(music.begin() + index);
}

void AudioCache::clearChunks() noexcept
{
	for (Mix_Chunk *chunk : chunks)
		Mix_FreeChunk(chunk);
	chunks.clear();
}

void AudioCache::clearMusic() noexcept
{
	for (Mix_Music *music : music)
		Mix_FreeMusic(music);
	music.clear();
}