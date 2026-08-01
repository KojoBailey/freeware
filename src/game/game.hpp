#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

class Game : public IGame {
public:
	auto start(GameEngine& engine) -> Result<Nothing> override;

    auto update(F64 deltaTime) -> Result<Nothing> override;

private:
	F64 timeElapsed;

	GameObject background;
	Vector<GameObject> apps;

	SharedPtr<Texture> vimTexture;
};
