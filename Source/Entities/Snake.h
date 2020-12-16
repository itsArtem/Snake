#pragma once

#include "Mob.h"
#include "../Application.h"

#include <SDL_Rect.h>

#include <vector>
#include <memory>

class GameplayState;

class Snake final : public Mob
{
public:
	Snake(SDL_FPoint pos, GameplayState &gameplayState, Application &app) noexcept;

	void update(float delta) noexcept override;
	void render(SDL_Renderer *renderer) const noexcept override;

private:
	GameplayState &gameplayState;
	Application &app;

	class Body final : public Mob
	{
	public:
		const Mob &parent;

		bool highlight = false;
		bool dim = false;
		float gm = static_cast<float>(colourMod.g);
		float bm = static_cast<float>(colourMod.b);

		Body(const Mob &parent, SDL_FPoint pos, const Application &app) noexcept;
		
		void update(float delta) noexcept override;
	};

	std::vector<std::unique_ptr<Body>> bodies;
	float gameOverTimer = 5.0f;
	bool gameOver = false;
};