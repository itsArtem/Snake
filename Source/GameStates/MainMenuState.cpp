#include "MainMenuState.h"
#include "../Graphics/Gui/Button.h"
#include "GameplayState.h"
#include "AboutMenuState.h"

#include <SDL_render.h>

#include <memory>

MainMenuState::MainMenuState(Application &app) noexcept
	: app{app}
{
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);

	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 140.0f}, true, Text{"Play", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255}, 
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 180.0f}, true, Text{"About", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255},
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 220.0f}, true, Text{"Quit", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255},
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
}

void MainMenuState::update() noexcept
{
	canvas.update();

	if (canvas.getButton(0)->wasReleased())
	{
		app.gameStateManager.add(std::make_unique<GameplayState>(app));
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 2);
	}
	else if (canvas.getButton(1)->wasReleased())
		app.gameStateManager.add(std::make_unique<AboutMenuState>(app));
	else if (canvas.getButton(2)->wasReleased())
		app.quit();
}

void MainMenuState::render() const noexcept
{
	SDL_Renderer *const renderer = app.getRenderer();
	canvas.render(renderer);
	
	SDL_Point windowSize;
	SDL_GetWindowSize(app.getWindow(), &windowSize.x, &windowSize.y);
	title.render({windowSize.x / 2.0f - title.getSize().x / 2.0f, 24.0f}, renderer);
	highscoreLabel.render({8.0f, windowSize.y - 28.0f}, renderer);
	highscoreCount.render({highscoreLabel.getSize().x + 16.0f, windowSize.y - 28.0f}, renderer);
}
