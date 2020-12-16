#include "AboutMenuState.h"

#include <SDL_Render.h>
#include <SDL_keyboard.h>

AboutMenuState::AboutMenuState(Application &app) noexcept
	: app{app}
{
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);

	back.setText(Text{"Back", app.fontCache.get(1), app.getRenderer(), SDL_Colour{120, 120, 255, 255}});
	back.hoverColourMod = SDL_Colour{150, 150, 200, 255};
	back.pressedColourMod = SDL_Colour{80, 80, 80, 255};
	back.clickSound = app.audioCache.getChunk(3);
	back.pos.x = centre / 2.0f - back.getSize().x / 2.0f;
	back.pos.y = 420.0f;
}

void AboutMenuState::update() noexcept
{
	back.update();
	if (!escPressed && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
		escPressed = true;
	else if (back.wasReleased() || escPressed && !SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
	{
		app.gameStateManager.requestRemoval(app.gameStateManager.getSize() - 1);
		escPressed = false;
	}
}

void AboutMenuState::render() const noexcept
{
	SDL_Renderer *const renderer = app.getRenderer();
	
	int centre;
	SDL_GetWindowSize(app.getWindow(), &centre, nullptr);
	title.render({centre / 2.0f - title.getSize().x / 2.0f, 24.0f}, renderer);
	info.render({centre / 2.0f - info.getSize().x / 2.0f, 80.0f}, renderer);

	back.render(renderer);
}
