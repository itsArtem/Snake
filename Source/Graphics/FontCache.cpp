#include "FontCache.h"

#include <utility>
#include <stdexcept>

FontCache::FontCache() = default;

FontCache::FontCache(FontCache &&fontCache) noexcept
	: fonts{std::move(fontCache.fonts)}
{
}

FontCache::~FontCache()
{
	closeAll();
}

FontCache &FontCache::operator=(FontCache &&fontCache) noexcept
{
	closeAll();
	fonts = std::move(fontCache.fonts);
	return *this;
}

void FontCache::open(const std::string &path, int size)
{
	TTF_Font *font = TTF_OpenFont(path.c_str(), size);
	if (!font)
		throw std::runtime_error{SDL_GetError()};
	fonts.emplace_back(font);
}

void FontCache::close(std::vector<TTF_Font *>::size_type index) noexcept
{
	TTF_CloseFont(fonts[index]);
	fonts.erase(fonts.begin() + index);
}

void FontCache::closeAll() noexcept
{
	for (TTF_Font *font : fonts)
		TTF_CloseFont(font);
	fonts.clear();
}
