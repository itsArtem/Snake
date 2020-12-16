#include "GameplayState.h"
#include "../Application.h"
#include "../Entities/Snake.h"
#include "../AudioCache.h"
#include "PauseMenuState.h"

#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_rect.h>
#include <SDL_keyboard.h>
#include <SDL_mixer.h>

#include <memory>
#include <random>
#include <chrono>

GameplayState::GameplayState(Application &app) noexcept
	: app{app}
{
	entityManager.addMob(std::make_unique<Snake>(SDL_FPoint{304.0f, 224.0f}, *this, app));
	for (int i = 0; i < 5; ++i)
		spawnFood();
}

void GameplayState::update() noexcept
{
	entityManager.update(app.getDelta());

	foodSpawnTimer -= 1 * app.getDelta();
	if (foodSpawnTimer <= 0.0f)
	{
		spawnFood();
		Mix_PlayChannel(1, app.audioCache.getChunk(1), 0);
		foodSpawnTimer = foodSpawnDelay;
	}
	
	if (lastScore != score)
	{
		lastScore = score;
		scoreCount.setText(std::to_string(score), app.fontCache.get(0), app.getRenderer(), countColour, true);
	}

	if (score > app.saveData.highscore)
	{
		app.saveData.highscore = score;
		highscoreCount.setText(std::to_string(app.saveData.highscore), app.fontCache.get(0), app.getRenderer(), countColour, true);
	}

	if (!pausePressed && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
		pausePressed = true;
	else if (pausePressed && !SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
	{
		app.gameStateManager.add(std::make_unique<PauseMenuState>(app));
		pausePressed = false;
	}
}

void GameplayState::render() const noexcept
{
	SDL_Renderer *const renderer = app.getRenderer();
	entityManager.render(renderer);

	scoreLabel.render({8.0f, 8.0f}, renderer);
	scoreCount.render({scoreLabel.getSize().x + 16.0f, 8.0f}, renderer);
	highscoreLabel.render({8.0f, 32.0f}, renderer);
	highscoreCount.render({highscoreLabel.getSize().x + 16.0f, 32.0f}, renderer);
}

void GameplayState::spawnFood() noexcept
{
	std::default_random_engine engine;
	engine.seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution dist{0};
	const SDL_Rect src{[&engine, &dist]
		{
			const int type = dist(engine) % 4;
			switch (type)
			{
			case 0:
				return SDL_Rect{32, 0, 8, 8};
			case 1:
				return SDL_Rect{40, 0, 8, 8};
			case 2:
				return SDL_Rect{32, 8, 8, 8};
			default:
				return SDL_Rect{40, 8, 8, 8};
			}
		}()
	};
	SDL_Point windowSize;
	SDL_GetWindowSize(app.getWindow(), &windowSize.x, &windowSize.y);
	entityManager.addFood(std::make_unique<Food>(SDL_FPoint{dist(engine) % static_cast<int>(windowSize.x / Food::size) * Food::size, dist(engine) % static_cast<int>(windowSize.y / Food::size) * Food::size}, app.textureCache.get(0), src));
}
