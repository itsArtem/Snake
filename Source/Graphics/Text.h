#pragma once

#include <SDL_render.h>
#include <SDL_rect.h>
#include <SDL_pixels.h>
#include <SDL_ttf.h>

#include <string>
#include <cstdint>

class Text final
{
public:
	Text() = default;

	Text(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour colour = {255, 255, 255, 255}, bool blended = false)
	{
		setText(text, font, renderer, colour, blended);
	}

	Text(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour fg, SDL_Colour bg)
	{
		setText(text, font, renderer, fg, bg);
	}

	Text(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, std::uint32_t wrapLength, SDL_Point size, SDL_Colour colour = {255, 255, 255, 255})
	{
		setText(text, font, renderer, wrapLength, size, colour);
	}

	Text(const Text &text) = delete;
	Text(Text &&text) noexcept;

	~Text();

	Text &operator =(const Text &text) = delete;
	Text &operator =(Text &&text) noexcept;

	void setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour colour = {255, 255, 255, 255}, bool blended = false);
	void setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour fg, SDL_Colour bg);
	void setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, std::uint32_t wrapLength, SDL_Point size, SDL_Colour colour = {255, 255, 255, 255});

	[[nodiscard]] SDL_Colour getColourMod() const noexcept;
	void setColourMod(SDL_Colour colourMod) noexcept;
	[[nodiscard]] SDL_Point getSize() const noexcept { return size; }

	void render(SDL_FPoint pos, SDL_Renderer *renderer) const noexcept;

private:
	SDL_Texture *texture = nullptr;
	SDL_Point size{0, 0};

	void createTexture(SDL_Surface *surface, SDL_Renderer *renderer);
};