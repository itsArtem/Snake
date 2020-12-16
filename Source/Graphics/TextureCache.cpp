#include "TextureCache.h"

#include <SDL_image.h>

#include <utility>
#include <stdexcept>

TextureCache &TextureCache::operator=(TextureCache &&textureCache) noexcept
{
	clear();
	textures = std::move(textureCache.textures);
	return *this;
}

void TextureCache::load(const std::string &path, SDL_Renderer *renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture)
		throw std::runtime_error{SDL_GetError()};
	textures.emplace_back(texture);
}

void TextureCache::remove(std::vector<SDL_Texture *>::size_type index) noexcept
{
	SDL_DestroyTexture(textures[index]);
	textures.erase(textures.begin() + index);
}

void TextureCache::clear() noexcept
{
	for (SDL_Texture *texture : textures)
		SDL_DestroyTexture(texture);
	textures.clear();
}
