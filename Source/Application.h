#pragma once

#include "Graphics/TextureCache.h"
#include "AudioCache.h"
#include "Graphics/FontCache.h"
#include "GameStates/GameStateManager.h"
#include "SaveData.h"

#include <SDL_video.h>
#include <SDL_render.h>

class Application final
{
public:
	TextureCache textureCache;
	AudioCache audioCache;
	FontCache fontCache;

	GameStateManager gameStateManager;
	SaveData saveData{"Resources/Highscore.sav"};
	
	Application();
	Application(const Application &) = delete;
	Application(Application &&app) = delete;

	~Application();

	Application &operator =(const Application &) = delete;
	Application &operator =(Application &&app) = delete;

	void run() noexcept;
	void quit() noexcept;

	[[nodiscard]] float getDelta() const noexcept { return delta; }
	[[nodiscard]] SDL_Window *getWindow() const noexcept { return window; }
	[[nodiscard]] SDL_Renderer *getRenderer() const noexcept { return renderer; }

private:
	bool running = false;

	SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	float delta = 0.0f;

	void update() noexcept;
	void render() const noexcept;
};