#pragma once

#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

#include <cmath>

template<U8 columnCount, U8 rowCount>
class Grid {
public:
	static auto create(GameEngine& engine) -> Result<Grid>
	{
		Grid result;

		result.object = engine.createGameObject();

		result.object.addComponent<RectTransform>()
			.withPosition({ .x = 260, .y = 20 });

		return result;
	}

	auto getPos() const -> Vec2<F32>
	{
		const auto* rectTransform = object.getComponent<RectTransform>();
		assertValidPtr(rectTransform);
		return rectTransform->position;
	}

	auto getIndex(const I8 column, const I8 row) const -> USz
	{
		return row * columnCount + column;
	}

	auto posToIndex(const Vec2<F32> target) const -> Vec2<I8>
	{
		return {
			.x = static_cast<I8>(std::floor((target.x - getPos().x) / tileSize.x)),
			.y = static_cast<I8>(std::floor((target.y - getPos().y) / tileSize.y)),
		};
	}

	auto snapToTileCenter(const I8 column, const I8 row) const -> Maybe<Vec2<F32>>
	{
		if ((column < 0) or (column >= columnCount) or (row < 0) or (row >= rowCount)) {
			return std::nullopt;
		}
		return Vec2<F32>{
			.x = (column * tileSize.x) + getPos().x + (tileSize.x / 2.0f),
			.y = (row * tileSize.y) + getPos().y + (tileSize.y / 2.0f),
		};
	}

	auto snapToTileCenter(Vec2<F32> target) const -> Maybe<Vec2<F32>>
	{
		const Vec2<I8> index = posToIndex(target);
		return snapToTileCenter(index.x, index.y);
	}

	void occupyTile(const I8 column, const I8 row)
	{
		isTileXOccupied.set(getIndex(column, row));
	}

	void occupyTile(const Vec2<F32> target)
	{
		const Vec2<I8> index = posToIndex(target);
		occupyTile(index.x, index.y);
	}

	auto isTileFree(const I8 column, const I8 row) const -> Bool
	{
		if (column < 0 or row < 0 or column >= columnCount or row >= rowCount) {
			return false;
		}
		const USz index = getIndex(column, row);
		return not isTileXOccupied.test(index);
	}

	auto isTileFree(const Vec2<F32> target) const -> Bool
	{
		const Vec2<I32> index = posToIndex(target);
		return isTileFree(index.x, index.y);
	}

private:
	static constexpr USz tileCount = columnCount * rowCount;
	GameObject object;

	Bitset<tileCount> isTileXOccupied;
	static constexpr Vec2<F32> tileSize{ .x = 100, .y = 100 };
};
