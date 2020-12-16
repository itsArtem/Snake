#pragma once

class GameState
{
public:
	virtual ~GameState() = 0;

	virtual void update() noexcept = 0;
	virtual void render() const noexcept = 0;
	
protected:
	GameState(const GameState &gameState) = default;
	GameState(GameState &&gameState) = default;

	GameState() = default;
	
	GameState &operator =(const GameState &gameState) = default;
	GameState &operator =(GameState &&gameState) = default;
};