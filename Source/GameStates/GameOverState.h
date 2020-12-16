#pragma once

#include "GameState.h"
#include "../Application.h"
#include "../Graphics/Gui/GuiCanvas.h"
#include "../Graphics/Text.h"

class GameplayState;

class GameOverState final : public GameState
{
public:
	GameOverState(Application &app, const GameplayState &gameplayState) noexcept;

	virtual void update() noexcept;
	virtual void render() const noexcept;

private:
	Application &app;
	GuiCanvas canvas;
	const Text title{"Game Over!", app.fontCache.get(2), app.getRenderer(), {80, 200, 100, 255}};
	const Text msg{"Aww! You lose!", app.fontCache.get(0), app.getRenderer(), {200, 80, 80, 255}, true};
	const Text scoreLabel{"Score:", app.fontCache.get(0), app.getRenderer(), {60, 120, 60, 255}, true};
	const Text scoreCount;
	const Text highscoreLabel{"Highscore:", app.fontCache.get(0), app.getRenderer(), {60, 120, 60, 255}};
	const Text highscoreCount;
};