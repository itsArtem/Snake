#pragma once

#include <SDL_ttf.h>

#include <string>
#include <vector>

class FontCache final
{
public:
	FontCache();
	FontCache(const FontCache &fontCache) = delete;
	FontCache(FontCache &&fontCache) noexcept;

	~FontCache();

	FontCache &operator =(const FontCache &fontCache) = delete;
	FontCache &operator =(FontCache &&fontCache) noexcept;

	void open(const std::string &path, int size);

	void close(std::vector<TTF_Font *>::size_type index) noexcept;
	void closeAll() noexcept;

	[[nodiscard]] TTF_Font *get(std::vector<TTF_Font *>::size_type index) const noexcept { return fonts[index]; }

private:
	std::vector<TTF_Font *> fonts;
};