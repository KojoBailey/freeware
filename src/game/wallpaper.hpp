#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

class Wallpaper {
public:
	auto init(GameEngine& engine) -> Result<Nothing>;

private:
	GameObject wallpaper;
};
