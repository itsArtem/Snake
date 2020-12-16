#include "GameStateManager.h"

void GameStateManager::requestRemoval(std::vector<std::unique_ptr<GameState>>::size_type index) noexcept
{
    queuedRemovalIndex = index;
    queuedRemoval = true;
}

void GameStateManager::update() noexcept
{
    gameStates.back()->update();
    if (queuedRemoval)
    {
        gameStates.erase(gameStates.begin() + queuedRemovalIndex);
        queuedRemoval = false;
    }
}

void GameStateManager::render() const noexcept
{
    if (overlay)
        gameStates[overlayIndex]->render();
    gameStates.back()->render();
}

void GameStateManager::setOverlay(bool overlay) noexcept
{
    this->overlay = overlay;
    if (overlay)
        overlayIndex = gameStates.size() - 2;
}
