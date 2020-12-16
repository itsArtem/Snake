#include "SaveData.h"

#include <fstream>

bool SaveData::serialize() const noexcept
{
	std::ofstream stream{path, std::ofstream::binary};
	if (!stream)
		return false;
	stream.write(reinterpret_cast<const char *>(&highscore), sizeof(highscore));
	stream.close();
	std::ios_base::in;
	return stream.good();
}

bool SaveData::deserialize() noexcept
{
	std::ifstream stream{path, std::ofstream::binary};
	if (!stream)
		return false;
	stream.read(reinterpret_cast<char *>(&highscore), sizeof(highscore));
	stream.close();

	return stream.good();
}
