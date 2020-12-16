#include "Application.h"
#include "GameStates/MainMenuState.h"

#include <SDL_events.h>
#include <SDL_error.h>
#include <SDL_mixer.h>

#include <utility> 
#include <stdexcept>
#include <chrono>

Application::Application()
{
	if (!window || !renderer)
	{
		if (window) SDL_DestroyWindow(window);
		else if (renderer) SDL_DestroyRenderer(renderer);

		throw std::runtime_error{SDL_GetError()};
	}

	textureCache.load("Resources/SpriteSheet.png", renderer);
	
	audioCache.loadChunk("Resources/Audio/Eat.wav");
	audioCache.loadChunk("Resources/Audio/FoodSpawn.wav");
	audioCache.loadChunk("Resources/Audio/GameOver.wav");
	audioCache.loadChunk("Resources/Audio/Press.wav");
	audioCache.loadMusic("Resources/Audio/BackgroundTrack.mid");
	Mix_PlayMusic(audioCache.getMusic(0), -1);

	fontCache.open("Resources/Font.ttf", 24);
	fontCache.open("Resources/Font.ttf", 32);
	fontCache.open("Resources/Font.ttf", 48);

	if (saveData.doesExist())
		saveData.deserialize();
	else
		saveData.serialize();

	gameStateManager.add(std::make_unique<MainMenuState>(*this));
}

Application::~Application()
{
	textureCache.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Application::run() noexcept
{
	running = true;
	using std::chrono::steady_clock;
	steady_clock::time_point lastTime{steady_clock::now()};

	while (running)
	{
		steady_clock::time_point now{steady_clock::now()};
		delta = (now - lastTime).count() / 1e9f;
		lastTime = now;

		update();
		render();
	}
}

void Application::quit() noexcept
{
	running = false;
	saveData.serialize();
}

void Application::update() noexcept
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		if (event.type == SDL_QUIT)
			quit();

	gameStateManager.update();
}

void Application::render() const noexcept
{
	gameStateManager.render();
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
