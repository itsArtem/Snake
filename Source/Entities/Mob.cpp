#include "Mob.h"

Mob::~Mob() = default;

void Mob::update(float delta) noexcept
{
	tf.x += velocity.x * delta;
	tf.y += velocity.y * delta;
}

void Mob::render(SDL_Renderer *renderer) const noexcept
{
	SDL_SetTextureColorMod(spriteSheet, colourMod.r, colourMod.g, colourMod.b);
	SDL_SetTextureAlphaMod(spriteSheet, colourMod.a);
	SDL_RenderCopyF(renderer, spriteSheet, &src, &tf);
}

Mob::Mob(SDL_FRect tf, SDL_Texture *spriteSheet, SDL_Rect src) noexcept
	: Entity{tf},
	spriteSheet{spriteSheet},
	src{src}
{
}