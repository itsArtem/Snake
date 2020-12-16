#pragma once

#include "Entity.h"

#include <SDL_rect.h>
#include <SDL_pixels.h>

class Mob : public Entity
{
public:
	SDL_FPoint velocity{0.0f, 0.0f};

	virtual ~Mob() = 0;

	virtual void update(float delta) noexcept;
	void render(SDL_Renderer *renderer) const noexcept override;

protected:
	SDL_Colour colourMod{255, 255, 255, 255};

	Mob(SDL_FRect tf, SDL_Texture *spriteSheet, SDL_Rect src) noexcept;
	Mob(const Mob &mob) = delete;
	Mob(Mob &&mob) = default;

	Mob &operator =(const Mob &mob) = delete;
	Mob &operator =(Mob &&mob) = default;

private:
	SDL_Texture *spriteSheet;
	SDL_Rect src;
};