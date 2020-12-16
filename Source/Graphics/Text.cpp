#include "Text.h"

#include <stdexcept>
#include <utility>

Text::Text(Text &&text) noexcept
	: texture{text.texture},
	size{std::move(text.size)}
{
	text.texture = nullptr;
}

Text::~Text()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

Text &Text::operator =(Text &&text) noexcept
{
	if (texture)
		SDL_DestroyTexture(texture);

	texture = text.texture;
	text.texture = nullptr;
	size = std::move(text.size);
	return *this;
}

void Text::setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour colour, bool blended)
{
	createTexture(blended ? TTF_RenderText_Blended(font, text.c_str(), colour) : TTF_RenderText_Solid(font, text.c_str(), colour), renderer);
	TTF_SizeText(font, text.c_str(), &size.x, &size.y);
}

void Text::setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, SDL_Colour fg, SDL_Colour bg)
{
	createTexture(TTF_RenderText_Shaded(font, text.c_str(), fg, bg), renderer);
	TTF_SizeText(font, text.c_str(), &size.x, &size.y);
}

void Text::setText(const std::string &text, TTF_Font *font, SDL_Renderer *renderer, std::uint32_t wrapLength, SDL_Point size, SDL_Colour colour)
{
	createTexture(TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, wrapLength), renderer);
	this->size = size;
}

SDL_Colour Text::getColourMod() const noexcept
{
	SDL_Colour colour;
	SDL_GetTextureColorMod(texture, &colour.r, &colour.g, &colour.b);
	SDL_GetTextureAlphaMod(texture, &colour.a);
	return colour;
}

void Text::setColourMod(SDL_Colour colourMod) noexcept
{
	SDL_SetTextureColorMod(texture, colourMod.r, colourMod.g, colourMod.b);
	SDL_SetTextureAlphaMod(texture, colourMod.a);
}

void Text::render(SDL_FPoint pos, SDL_Renderer *renderer) const noexcept
{
	const SDL_FRect dst{pos.x, pos.y, static_cast<float>(size.x), static_cast<float>(size.y)};
	SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

void Text::createTexture(SDL_Surface *surface, SDL_Renderer *renderer)
{
	if (!surface)
		throw std::runtime_error{SDL_GetError()};
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		throw std::runtime_error{SDL_GetError()};
}