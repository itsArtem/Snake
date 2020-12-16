#pragma once

#include "GameState.h"
#include "../Application.h"
#include "../Entities/EntityManager.h"
#include "../Graphics/Text.h"
#include "../Graphics/FontCache.h"

#include <string>

class GameplayState final : public GameState
{
public:
	int score = 0;
	EntityManager entityManager;

	GameplayState(Application &app) noexcept;

	void update() noexcept override;
	void render() const noexcept override;

private:
	Application &app;

	int lastScore = 0;
	const SDL_Colour countColour{255, 255, 100, 255};

	const Text scoreLabel{"Score:", app.fontCache.get(0), app.getRenderer(), {255, 255, 255, 255}, true};
	Text scoreCount{std::to_string(score), app.fontCache.get(0), app.getRenderer(), countColour, true};

	const Text highscoreLabel{"Highscore:", app.fontCache.get(0), app.getRenderer(), {255, 255, 255, 255}, true};
	Text highscoreCount{std::to_string(app.saveData.highscore), app.fontCache.get(0), app.getRenderer(), countColour, true};

	const float foodSpawnDelay = 6.0f;
	float foodSpawnTimer = foodSpawnDelay;

	bool pausePressed = false;

	void spawnFood() noexcept;
};