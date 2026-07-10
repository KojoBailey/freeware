#include "SDL3/Texture.hpp"
#include "SDL3/Rect.hpp"
#include "SDL3/Vec.hpp"

#include <filesystem>

using namespace sdl;

enum class AppType {
	Vim,
	Paint,
};

class App {
public:
	constexpr float SIZE = 70.0f;

	[[nodiscard]] auto create(const std::filesystem::path& texturePath)
		-> std::expected<App, std::string>
	{
		auto maybeTexture = renderer.loadTexture("./assets/Vim.png");
		if (not maybeTexture.has_value()) {
			return maybeTexture.error();
		}
		texture = *maybeTexture;

		rect = {
			.size {
				.x = SIZE,
				.y = SIZE,
			},
		};
		rect.anchorMiddle();
	}

private:
	Texture texture;
	Rect<float> rect;
};
