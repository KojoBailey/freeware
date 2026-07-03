#ifndef KOJO_SDL3_SPRITE_HPP
#define KOJO_SDL3_SPRITE_HPP

#include "Texture.hpp"
#include "Rect.hpp"
#include "Clock.hpp"

namespace sdl {

class Sprite {
public:
	Sprite(Texture& _texture, const Rect<float>& _rect)
		: texture{_texture}, rect{_rect} {}

	auto getSdlFRect() const -> SDL_FRect
	{
		return rect.toSdlFRect();
	}

	auto getSdlTexture() -> SDL_Texture*
	{
		return texture.get();
	}

	[[nodiscard]] constexpr auto getSize() const -> Vec<float, 2>
	{
		return rect.size;
	}

	[[nodiscard]] constexpr auto getPos() const -> Vec<float, 2>
	{
		return rect.position;
	}

	[[nodiscard]] auto getTicksSinceBirth() const -> std::uint64_t
	{
		return clock.getTicks();
	}

	[[nodiscard]] auto getSecondsSinceBirth() const -> float
	{
		return clock.getSeconds();
	}

	void setPos(Vec<float, 2> newPos)
	{
		rect.position = newPos;
	}

	void setY(float newY)
	{
		rect.position.y = newY;
	}

	void changePos(Vec<float, 2> deltaPos)
	{
		rect.position += deltaPos;
	}

	void changeY(float deltaY)
	{
		rect.position.y += deltaY;
	}

	void anchorCenter()
	{
		rect.anchor = {
			.x = rect.size.x / 2.0f,
			.y = rect.size.y / 2.0f,
		};
	}

private:
	Texture& texture;
	Rect<float> rect;

	Clock clock;
};

}

#endif
