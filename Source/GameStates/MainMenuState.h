#pragma once

#include "GameState.h"
#include "../Application.h"
#include "../Graphics/Gui/GuiCanvas.h"
#include "../Graphics/Text.h"

#include <string>

class MainMenuState final : public GameState
{
public:
	MainMenuState(Application &app) noexcept;

	void update() noexcept override;
	void render() const noexcept override;

private:
	Application &app;
	GuiCanvas canvas;
	const Text title{"Snake", app.fontCache.get(2), app.getRenderer(), {80, 200, 100, 255}};
	const Text highscoreLabel{"Highscore:", app.fontCache.get(0), app.getRenderer(), {60, 140, 60, 255}, true};
	const Text highscoreCount{std::to_string(app.saveData.highscore), app.fontCache.get(0), app.getRenderer(), {180, 180, 100, 255}, true};
};