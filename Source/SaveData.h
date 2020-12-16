#pragma once

#include <string>
#include <filesystem>

class SaveData final
{
public:
	int highscore = 0;

	SaveData(const std::string &path) noexcept
		: path{path}
	{
	}

	bool serialize() const noexcept;
	bool deserialize() noexcept;

	[[nodiscard]] bool doesExist() const noexcept { return std::filesystem::exists(path); }
	
private:
	const std::string path;
};