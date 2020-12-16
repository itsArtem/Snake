#include "Snake.h"
#include "../GameStates/GameplayState.h"
#include "EntityManager.h"
#include "../Graphics/TextureCache.h"
#include "../AudioCache.h"
#include "../GameStates/GameOverState.h"

#include <SDL_keyboard.h>
#include <SDL_video.h>
#include <SDL_mixer.h>

#include <functional>
#include <cstdint>
#include <cmath>

Snake::Snake(SDL_FPoint pos, GameplayState &gameplayState, Application &app) noexcept
	: Mob{{pos.x, pos.y, 32.0f, 32.0f}, app.textureCache.get(0), {0, 0, 16, 16}},
	gameplayState{gameplayState},
	app{app}
{
}

void Snake::update(float delta) noexcept
{
	if (gameOver)
	{
		gameOverTimer -= 1 * delta;
		if (gameOverTimer <= 0.0f)
		{
			app.gameStateManager.add(std::make_unique<GameOverState>(app, gameplayState));
			app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 2);
		}
	}
	else
	{
		const std::uint8_t *keyboard = SDL_GetKeyboardState(nullptr);
		constexpr float speed = 100.0f;

		const bool up = keyboard[SDL_SCANCODE_W]; 
		const bool down = keyboard[SDL_SCANCODE_S];
		const bool left = keyboard[SDL_SCANCODE_A];
		const bool right = keyboard[SDL_SCANCODE_D];

		if ((up || down) && !left && !right && velocity.y == 0.0f)
		{
			velocity.x = 0.0f;
			if (keyboard[SDL_SCANCODE_W])
				velocity.y = -speed;
			else
				velocity.y = speed;
		}
		else if ((left || right) && !up && !down && velocity.x == 0.0f)
		{
			velocity.y = 0.0f;
			if (keyboard[SDL_SCANCODE_A])
				velocity.x = -speed;
			else
				velocity.x = speed;
		}

		Mob::update(delta);

		for (auto it{gameplayState.entityManager.getFoodBeginning()}; it != gameplayState.entityManager.getFoodEnd(); ++it)
		{
			if (tf.x + tf.w < it->get()->tf.x
				|| tf.x > it->get()->tf.x + it->get()->tf.w
				|| tf.y + tf.h < it->get()->tf.y
				|| tf.y > it->get()->tf.y + it->get()->tf.h)
				continue;

			it->get()->active = false;
			if (bodies.empty())
				bodies.emplace_back(std::make_unique<Body>(*this, SDL_FPoint{tf.x, tf.y}, app));
			else
				bodies.emplace_back(std::make_unique<Body>(*bodies.back(), SDL_FPoint{bodies.back()->tf.x, bodies.back()->tf.y}, app));
			++gameplayState.score;
			Mix_PlayChannel(0, app.audioCache.getChunk(0), 0);
		}

		SDL_Point windowSize;
		SDL_GetWindowSize(app.getWindow(), &windowSize.x, &windowSize.y);
		if (tf.x <= 0.0f || tf.x + tf.w >= windowSize.x || tf.y <= 0.0f || tf.y + tf.h >= windowSize.y)
		{
			gameOver = true;
			Mix_PlayChannel(2, app.audioCache.getChunk(2), 0);
		}
	}

	for (auto &body : bodies)
	{
		body->update(delta);

		std::function<bool(SDL_FPoint)> hasCollisionWithBody{[&body](SDL_FPoint point)
			{
				return point.x > body->tf.x && point.x < body->tf.x + body->tf.w && point.y > body->tf.y && point.y < body->tf.y + body->tf.h;
			}
		};

		if (!gameOver 
			&& &body->parent != this
			&& (velocity.x < 0.0f && (hasCollisionWithBody({tf.x, tf.y}) || hasCollisionWithBody({tf.x, tf.y + tf.h}))
				|| velocity.x > 0.0f && (hasCollisionWithBody({tf.x + tf.w, tf.y}) || hasCollisionWithBody({tf.x + tf.w, tf.y + tf.h}))
				|| velocity.y < 0.0f && (hasCollisionWithBody({tf.x, tf.y}) || hasCollisionWithBody({tf.x + tf.w, tf.y}))
				|| velocity.y > 0.0f && (hasCollisionWithBody({tf.x, tf.y + tf.h}) || hasCollisionWithBody({tf.x + tf.w, tf.y + tf.h}))))
		{
			Mix_PlayChannel(2, app.audioCache.getChunk(2), 0);
			gameOver = true;
			body->highlight = true;
			return;
		}
	}
}

void Snake::render(SDL_Renderer *renderer) const noexcept
{
	Mob::render(renderer);
	for (const auto &body : bodies)
		body->render(renderer);
}

Snake::Body::Body(const Mob &parent, SDL_FPoint pos, const Application &app) noexcept
	: Mob{{pos.x, pos.y, 30.0f, 30.0f}, app.textureCache.get(0), {16, 0, 16, 16}},
	parent{parent}
{
}

void Snake::Body::update(float delta) noexcept
{
	constexpr float speed = 100.0f;
	velocity.x = velocity.y = 0.0f;

	if (parent.velocity.x != 0.0f)
	{
		if (tf.x + tf.w < parent.tf.x)
			velocity.x = speed;
		else if (tf.x > parent.tf.x + parent.tf.w)
			velocity.x = -speed;

		if (tf.y < parent.tf.y + (parent.tf.h - tf.h) / 2.0f)
			velocity.y = speed;
		else if (tf.y > parent.tf.y + (parent.tf.h - tf.h) / 2.0f)
			velocity.y = -speed;
	}
	else if (parent.velocity.y != 0.0f)
	{
		if (std::ceil(tf.x) < parent.tf.x + (parent.tf.w - tf.w) / 2.0f)
			velocity.x = speed;
		else if (tf.x > std::ceil(parent.tf.x) + (parent.tf.w - tf.w) / 2.0f)
			velocity.x = -speed;

		if (tf.y + tf.h < parent.tf.y)
			velocity.y = speed;
		else if (tf.y > parent.tf.y + parent.tf.h)
			velocity.y = -speed;
	}

	Mob::update(delta);

	if (highlight)
	{
		if (!dim && gm > 50.0f)
		{
			gm -= 455.0f * delta;
			bm -= 455.0f * delta;
			if (gm <= 50.0f)
			{
				if (gm < 50.0f) gm = bm = 50.0f;
				dim = true;
			}
		}
		else if (dim)
		{
			gm += 455.0f * delta;
			bm += 455.0f * delta;
			if (gm >= 255.0f)
			{
				if (gm > 255.0f) gm = bm = 255.0f;
				dim = false;
			}
		}

		colourMod.g = static_cast<int>(gm);
		colourMod.b = static_cast<int>(bm);
	}
}
