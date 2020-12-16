#pragma once

#include "Button.h"

#include <SDL_render.h>

#include <vector>
#include <memory>
#include <utility>

class GuiCanvas final
{
public:
	void update() noexcept;
	void render(SDL_Renderer *renderer) const noexcept;

	void add(std::unique_ptr<Button> button) noexcept { buttons.emplace_back(std::move(button)); }
	void remove(std::vector<std::unique_ptr<Button>>::size_type index) noexcept { buttons.erase(buttons.begin() + index); }

	Button *getButton(std::vector<std::unique_ptr<Button>>::size_type index) const noexcept { return buttons[index].get(); }

private:
	std::vector<std::unique_ptr<Button>> buttons;
};