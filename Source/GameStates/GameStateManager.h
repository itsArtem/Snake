#pragma once

#include "GameState.h"

#include <vector>
#include <memory>
#include <utility>

class GameStateManager final
{
public:
	void add(std::unique_ptr<GameState> &&gameState) noexcept { gameStates.emplace_back(std::move(gameState)); }
	void requestRemoval(std::vector<std::unique_ptr<GameState>>::size_type index) noexcept;

	[[nodiscard]] std::vector<std::unique_ptr<GameState>>::size_type getSize() const noexcept { return gameStates.size(); }

	void update() noexcept;
	void render() const noexcept;

	void setOverlay(bool overlay) noexcept;

private:
	std::vector<std::unique_ptr<GameState>> gameStates;
	std::vector<std::unique_ptr<GameState>>::size_type overlayIndex = 0;
	bool overlay = false;
	std::vector<std::unique_ptr<GameState>>::size_type queuedRemovalIndex = 0;
	bool queuedRemoval = false;
};