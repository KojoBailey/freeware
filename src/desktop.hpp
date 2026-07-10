#ifndef MAIN_DESKTOP_HPP
#define MAIN_DESKTOP_HPP

#include "Game.hpp"
#include "Drawable.hpp"

#include "SDL3/Rect.hpp"
#include "SDL3/Renderer.hpp"
#include "SDL3/Texture.hpp"
#include "SDL3/Vec.hpp"

using namespace sdl;

class Desktop {
public:
	Desktop() = default;

	Desktop(const Vec<float, 2> windowSize, const float _aspectRatio)
		: aspectRatio{_aspectRatio}, rect{initRect(windowSize, _aspectRatio)} {}

	void setTexture(Texture* _texture)
	{
		texture = _texture;
	}

	auto getRect() const -> const Rect<float>&
	{
		return rect;
	}

	void draw() const
	{
		game.getRenderer().render(*texture, rect);
	}

private:
	float aspectRatio;
	Rect<float> rect;
	Texture* texture;

	[[nodiscard]] static auto initRect(const Vec<float, 2> windowSize, const float _aspectRatio)
		-> Rect<float>
	{
		const float width = windowSize.y * _aspectRatio;
		return {
			.position = {
				.x = (windowSize.x - width) / 2.0f,
				.y = 0,
			},
			.size = {
				.x = width,
				.y = windowSize.y,
			},
		};
	}
};

#endif
