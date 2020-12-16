#pragma once

#include "GameState.h"
#include "../Application.h"
#include "../Graphics/Gui/GuiCanvas.h"
#include "../Graphics/Text.h"

class PauseMenuState final : public GameState
{
public:
	PauseMenuState(Application &app) noexcept;

	void update() noexcept override;
	void render() const noexcept override;

private:
	Application &app;
	GuiCanvas canvas;
	Text title{"Paused", app.fontCache.get(2), app.getRenderer(), {80, 200, 100, 255}};
	bool escPressed = false;
};