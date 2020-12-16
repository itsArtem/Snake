#pragma once

#include "GameState.h"
#include "../Application.h"
#include "../Graphics/Text.h"
#include "../Graphics/Gui/Button.h"

class AboutMenuState final : public GameState
{
public:
	AboutMenuState(Application &app) noexcept;

	void update() noexcept override;
	void render() const noexcept override;

private:
	Application &app;
	const Text title{"About", app.fontCache.get(2), app.getRenderer(), {80, 200, 100, 255}};
	const Text info{"        Move around with WASD.\n"
					"    Grow larger and gain points by\n" 
					"                eating food.\n"
					" You lose if the snake bites itself or\n"
					"           goes out of bounds.\n"
					"\n"
					"   Made by Artem Katerynych using\n"
					"               C++ and SDL2.\n"
					"             August 4th, 2020", 
		app.fontCache.get(0), app.getRenderer(), 400, {440, 260}, {60, 120, 60, 255}};
	Button back;
	bool escPressed = false;
};