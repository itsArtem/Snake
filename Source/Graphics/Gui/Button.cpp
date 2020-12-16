#include "Button.h"

Button::Button(SDL_FPoint pos, bool centred, Text &&text, SDL_Colour hoverColourMod, SDL_Colour pressedColourMod, Mix_Chunk *clickSound) noexcept
	: pos{centred ? pos.x - text.getSize().x / 2 : pos.x, centred ? pos.y - text.getSize().y / 2 : pos.y},
    hoverColourMod{hoverColourMod},
    pressedColourMod{pressedColourMod},
	clickSound{clickSound},
    text{std::move(text)}
{
}

void Button::update() noexcept
{
	button = SDL_GetMouseState(&mouse.x, &mouse.y);

	if (button != SDL_BUTTON_LMASK)
		click.x = click.y = -1;
	else if (click.x == -1 && click.y == -1)
		click = mouse;

	button = SDL_GetMouseState(&mouse.x, &mouse.y);
	if (button != SDL_BUTTON_LMASK)
		click.x = click.y = -1;
	else if (click.x == -1 && click.y == -1)
		click = mouse;

	SDL_Rect bounds{static_cast<int>(pos.x), static_cast<int>(pos.y), text.getSize().x, text.getSize().y};
	hoveredOver = SDL_PointInRect(&mouse, &bounds);
	pressed = SDL_PointInRect(&click, &bounds);
	if (pressed)
		clickTime = std::chrono::steady_clock::now().time_since_epoch();
	released = !pressed && std::chrono::steady_clock::now().time_since_epoch() - clickTime < std::chrono::milliseconds{100};
	if (released)
	{
		clickTime = std::chrono::milliseconds::zero();
		if (clickSound)
			Mix_PlayChannel(3, clickSound, 0);
	}

	if (hoveredOver && !pressed)
		text.setColourMod(hoverColourMod);
	else if (pressed)
		text.setColourMod(pressedColourMod);
	else
		text.setColourMod({255, 255, 255, 255});
}
