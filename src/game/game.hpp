#include "../engine/engine.hpp"

#include "wallpaper.hpp"
#include "app.hpp"

class Game : public IGame {
public:
	auto init(GameEngine& engine) -> Result<Nothing> override;

    auto update(GameEngine& engine, F64 deltaTime) -> Result<Nothing> override;

private:
	F64 timeElapsed;

	Wallpaper wallpaper;
	Vector<App> apps;

	App appPreview;

	SharedPtr<Texture> vimTexture;
};
