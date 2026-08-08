#include "../engine/engine.hpp"

#include "wallpaper.hpp"
#include "grid.hpp"
#include "app.hpp"

class Game : public IGame {
public:
	auto init(GameEngine& engine) -> Result<Nothing> override;

    auto update(GameEngine& engine, F64 deltaTime) -> Result<Nothing> override;

private:
	F64 timeElapsed;

	Wallpaper wallpaper;
	GameObject firewall;
	GameObject bottomBar;
	Grid<8, 6> grid;
	Vector<App> apps;

	GameObject appPreview;

	SharedPtr<Texture> vimTexture;
};
