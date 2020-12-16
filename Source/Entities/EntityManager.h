#pragma once

#include "Mob.h"
#include "Food.h"

#include <SDL_render.h>

#include <vector>
#include <memory>

class EntityManager final
{
public:
	void addMob(std::unique_ptr<Mob> mob) noexcept { mobs.emplace_back(std::move(mob)); }
	void addFood(std::unique_ptr<Food> food) noexcept { this->food.emplace_back(std::move(food)); }

	auto removeMob(std::vector<std::unique_ptr<Mob>>::size_type index) noexcept { return mobs.erase(mobs.begin() + index); }
	auto removeFood(std::vector<std::unique_ptr<Food>>::size_type index) noexcept { return food.erase(food.begin() + index); }

	void update(float delta) noexcept;
	void render(SDL_Renderer *renderer) const noexcept;

	[[nodiscard]] auto getMobBeginning() const noexcept { return mobs.begin(); }
	[[nodiscard]] auto getFoodBeginning() const noexcept { return food.begin(); }
	[[nodiscard]] auto getMobEnd() const noexcept { return mobs.end(); }
	[[nodiscard]] auto getFoodEnd() const noexcept { return food.end(); }

private:
	std::vector<std::unique_ptr<Mob>> mobs;
	std::vector <std::unique_ptr<Food>> food;
};