#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

#include "background.hpp"
#include "app.hpp"

class Game : public IGame {
public:
	auto start(GameEngine& engine) -> Result<Nothing> override;

    auto update(F64 deltaTime) -> Result<Nothing> override;

private:
	F64 timeElapsed;

	Background background;
	Vector<App> apps;

	SharedPtr<Texture> vimTexture;
};
