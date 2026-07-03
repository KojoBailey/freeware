#include "SDL3/Vec.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <optional>

using namespace sdl;

template<std::uint8_t COLUMNS, std::uint8_t ROWS>
class Grid {
public:
	static constexpr std::uint8_t TILE_COUNT = COLUMNS * ROWS;

	Vec<float, 2> size;
	Vec<float, 2> position;

	Grid()
	{
		tiles.fill(false);
	}

	auto getIndex(const std::uint8_t column, const std::uint8_t row) const -> std::size_t
	{
		return row * COLUMNS + column;
	}

	auto posToIndex(const Vec<float, 2> target) const -> Vec<float, 2>
	{
		return {
			.x = std::floor((target.x - position.x) / size.x),
			.y = std::floor((target.y - position.y) / size.y),
		};
	}

	auto snap(Vec<float, 2> input) const -> std::optional<Vec<float, 2>>
	{
		const Vec<float, 2> index = posToIndex(input);
		if ((index.x < 0) or (index.x >= COLUMNS) or (index.y < 0) or (index.y >= ROWS)) {
			return {};
		}
		return Vec<float, 2>{
			.x = (index.x * size.x) + position.x,
			.y = (index.y * size.y) + position.y,
		};
	}

	void occupyTile(const std::uint8_t column, const std::uint8_t row)
	{
		tiles[getIndex(column, row)] = true;
	}

	void occupyTile(const Vec<float, 2> target)
	{
		const Vec<float, 2> index = posToIndex(target);
		occupyTile(index.x, index.y);
	}

	auto isTileFree(const std::uint8_t column, const std::uint8_t row) const -> bool
	{
		const std::size_t index = getIndex(column, row);
		if (index >= tiles.size()) {
			return false;
		}
		return not tiles[index];
	}

	auto isTileFree(const Vec<float, 2> target) const -> bool
	{
		const Vec<float, 2> index = posToIndex(target);
		return isTileFree(index.x, index.y);
	}

private:
	std::array<bool, ROWS * COLUMNS> tiles;
};
