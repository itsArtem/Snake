#pragma once

#include <SDL_render.h>

#include <vector>
#include <string>

class TextureCache final
{
public:
	TextureCache() = default;
	TextureCache(const TextureCache &) = delete;
	TextureCache(TextureCache&& textureCache) noexcept
		: textures{ std::move(textureCache.textures) }
	{
	}

	~TextureCache() { clear(); }

	TextureCache &operator =(const TextureCache &) = delete;
	TextureCache &operator =(TextureCache &&textureCache) noexcept;

	void load(const std::string &path, SDL_Renderer *renderer);
	void remove(std::vector<SDL_Texture *>::size_type index) noexcept;
	void clear() noexcept;

	[[nodiscard]] SDL_Texture *get(std::vector<SDL_Texture *>::size_type index) const noexcept { return textures[index]; }

private:
	std::vector<SDL_Texture *> textures;
};