#include "EntityManager.h"

void EntityManager::update(float delta) noexcept
{
	for (auto it{mobs.begin()}; it != mobs.end(); ++it)
	{
		it->get()->update(delta);
		if (!it->get()->active)
		{
			it = mobs.erase(it);
			if (it == mobs.end()) break;
		}
	}

	for (auto it{food.begin()}; it != food.end(); ++it)
	{
		if (!it->get()->active)
		{
			it = food.erase(it);
			if (it == food.end()) break;
		}
	}
}

void EntityManager::render(SDL_Renderer *renderer) const noexcept
{
	for (const auto &mob : mobs)
		mob->render(renderer);
	for (const auto &food : food)
		food->render(renderer);
}
