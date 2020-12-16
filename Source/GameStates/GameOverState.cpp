#include "GameOverState.h"
#include "GameplayState.h"
#include "MainMenuState.h"

#include <SDL_render.h>

#include <string>

GameOverState::GameOverState(Application &app, const GameplayState &gameplayState) noexcept
	: app{app},
	scoreCount{std::to_string(gameplayState.score), app.fontCache.get(0), app.getRenderer(), {60, 120, 60, 255}, true},
	highscoreCount{std::to_string(app.saveData.highscore), app.fontCache.get(0), app.getRenderer(), {60, 120, 60, 255}, true}
{
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);

	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 200.0f}, true, Text{"Restart", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255},
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
	canvas.add(std::make_unique<Button>(SDL_FPoint{centre / 2.0f, 240.0f}, true, Text{"Give Up on Life", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}}, SDL_Colour{150, 150, 200, 255},
		SDL_Colour{80, 80, 80, 255}, app.audioCache.getChunk(3)));
}

void GameOverState::update() noexcept
{
	canvas.update();

	if (canvas.getButton(0)->wasReleased())
	{
		app.gameStateManager.add(std::make_unique<GameplayState>(app));
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 2);
	}
	else if (canvas.getButton(1)->wasReleased())
	{
		app.gameStateManager.add(std::make_unique<MainMenuState>(app));
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 2);
	}
}

void GameOverState::render() const noexcept
{
	SDL_Renderer *const renderer = app.getRenderer();
	canvas.render(renderer);
	
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);
	title.render({centre / 2.0f - title.getSize().x / 2.0f, 24.0f}, renderer);
	const float msgCentre = centre / 2.0f - msg.getSize().x / 2.0f;
	msg.render({msgCentre, 72.0f}, renderer);
	scoreLabel.render({msgCentre, 102.0f}, renderer);
	scoreCount.render({msgCentre + scoreLabel.getSize().x + 8.0f, 102.0f}, renderer);
	highscoreLabel.render({msgCentre, 132.0f}, renderer);
	highscoreCount.render({msgCentre + highscoreLabel.getSize().x + 8.0f, 132.0f}, renderer);
}
