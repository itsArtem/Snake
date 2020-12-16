#pragma once

#include <SDL_mixer.h>

#include <vector>
#include <string>

class AudioCache final
{
public:
	AudioCache() = default;
	AudioCache(const AudioCache &audioCache) = delete;
	AudioCache(AudioCache &&audioCache) noexcept;

	~AudioCache();

	AudioCache &operator =(const AudioCache &audioCache) = delete;
	AudioCache &operator =(AudioCache &&audioCache) noexcept;

	void loadChunk(const std::string &path);
	void loadMusic(const std::string &path);

	void removeChunk(std::vector<Mix_Chunk>::size_type index) noexcept;
	void removeMusic(std::vector<Mix_Music>::size_type index) noexcept;
	void clearChunks() noexcept;
	void clearMusic() noexcept;

	[[nodiscard]] Mix_Chunk *getChunk(std::vector<Mix_Chunk>::size_type index) const noexcept { return chunks[index]; }
	[[nodiscard]] Mix_Music *getMusic(std::vector<Mix_Music>::size_type index) const noexcept { return music[index]; }


private:
	std::vector<Mix_Chunk *> chunks;
	std::vector<Mix_Music *> music;
};