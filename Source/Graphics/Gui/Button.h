#pragma once

#include "../Text.h"

#include <SDL_mouse.h>
#include <SDL_rect.h>
#include <SDL_mixer.h>

#include <utility>
#include <chrono>
#include <cstdint>

class Button final
{
public:
	SDL_FPoint pos{0.0f, 0.0f};
	SDL_Colour hoverColourMod{255, 255, 255, 255};
	SDL_Colour pressedColourMod{255, 255, 255, 255};
	Mix_Chunk *clickSound = nullptr;

	Button() = default;
	Button(SDL_FPoint pos, bool centred, Text &&text, SDL_Colour hoverColourMod, SDL_Colour pressedColourMod, Mix_Chunk *clickSound) noexcept;

	void setText(Text &&text) noexcept { this->text = std::move(text); }

	void update() noexcept;
	void render(SDL_Renderer *renderer) const noexcept { text.render(pos, renderer); }

	[[nodiscard]] bool isHoveredOver() const noexcept { return hoveredOver; }
	[[nodiscard]] bool isPressed() const noexcept { return pressed; }
	[[nodiscard]] bool wasReleased() const noexcept { return released; }

	[[nodiscard]] SDL_Point getSize() const noexcept { return text.getSize(); }

private:
	Text text;
	
	SDL_Point mouse{-1, -1};
	SDL_Point click{-1, -1};
	std::uint32_t button = SDL_GetMouseState(&mouse.x, &mouse.y);
	std::chrono::steady_clock::duration clickTime{std::chrono::milliseconds::zero()};
	bool hoveredOver = false;
	bool pressed = false, released = false;
};