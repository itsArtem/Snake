#pragma once

#include <SDL_render.h>
#include <SDL_rect.h>

class Entity
{
public:
	bool active = true;
	SDL_FRect tf;

	virtual ~Entity() = 0;

	virtual void render(SDL_Renderer *renderer) const noexcept = 0;

protected:
	explicit Entity(SDL_FRect tf) noexcept
		: tf{tf}
	{
	}

	Entity(const Entity &entity) = default;
	Entity(Entity &&entity) = default;

	Entity &operator =(const Entity &entity) = default;
	Entity &operator =(Entity &&entity) = default;
};