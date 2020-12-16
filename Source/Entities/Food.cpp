#include "Food.h"

Food::Food(SDL_FPoint pos, SDL_Texture *texture, SDL_Rect src) noexcept
	: Entity{{pos.x, pos.y, size, size}},
	texture{texture},
	src{src}
{
}

void Food::render(SDL_Renderer *renderer) const noexcept
{
	SDL_SetTextureColorMod(texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_RenderCopyF(renderer, texture, &src, &tf);
}