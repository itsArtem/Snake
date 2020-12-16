#include "GuiCanvas.h"

void GuiCanvas::update() noexcept
{
	for (auto &button : buttons)
		button->update();
}

void GuiCanvas::render(SDL_Renderer *renderer) const noexcept
{
	for (const auto &button : buttons)
		button->render(renderer);
}
