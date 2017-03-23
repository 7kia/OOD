#include "stdafx.h"
#include "IShape.h"

struct SColor
{
	SColor(uint8_t r, uint8_t g, uint8_t b);
	SColor(const std::string &value);
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	bool operator==(const SColor & other) const;
};

IShape::~IShape()
{
}

std::ostream& operator<<(std::ostream& stream, const sf::Color color)
{
	stream << "#" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.r)
		<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.g)
		<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.b)
		<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.a);
	return stream;
}

sf::Color ToColor(const std::string & value)
{
	sf::Color result;
	if ((value[0] == '#') && (value.size() == 9))
	{
		std::istringstream valueRed(value.substr(1, 2));
		std::istringstream valueGreen(value.substr(3, 2));
		std::istringstream valueBlue(value.substr(5, 2));
		std::istringstream valueAlpha(value.substr(7, 2));
		int inputValue;
		valueRed >> std::hex >> inputValue;
		result.r = static_cast<uint8_t>(inputValue);

		valueGreen >> std::hex >> inputValue;
		result.g = static_cast<uint8_t>(inputValue);

		valueBlue >> std::hex >> inputValue;
		result.b = static_cast<uint8_t>(inputValue);

		valueAlpha >> std::hex >> inputValue;
		result.a = static_cast<uint8_t>(inputValue);
	}
	else
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_VALUE);
	}

	return result;
}