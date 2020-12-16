#pragma once

#include "Entity.h"

#include <SDL_render.h>

class Food final : public Entity
{
public:
	static constexpr float size = 24.0f;

	Food(SDL_FPoint pos, SDL_Texture *texture, SDL_Rect src) noexcept;

	void render(SDL_Renderer *renderer) const noexcept override;

private:
	SDL_Texture *texture;
	const SDL_Rect src;
};