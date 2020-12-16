#include "PauseMenuState.h"
#include "../Graphics/Gui/Button.h"
#include "GameplayState.h"
#include "MainMenuState.h"

#include <SDL_render.h>
#include <SDL_keyboard.h>

#include <memory>

PauseMenuState::PauseMenuState(Application &app) noexcept
	: app{app}
{
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);

	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 140.0f}, true, Text{"Resume", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255}, 
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 180.0f}, true, Text{"Main Menu", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255},
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));

	app.saveData.serialize();
}

void PauseMenuState::update() noexcept
{
	canvas.update();

	if (!escPressed && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
		escPressed = true;

	if (canvas.getButton(0)->wasReleased() || escPressed && !SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
	{
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 1);
		escPressed = false;
	}
	else if (canvas.getButton(1)->wasReleased())
	{
		app.gameStateManager.add(std::make_unique<MainMenuState>(app));
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 2);
	}
}

void PauseMenuState::render() const noexcept
{
	SDL_Renderer *const renderer = app.getRenderer();
	canvas.render(renderer);
	
	SDL_Point windowSize;
	SDL_GetWindowSize(app.getWindow(), &windowSize.x, &windowSize.y);
	title.render({windowSize.x / 2.0f - title.getSize().x / 2.0f, 24.0f}, renderer);
}
