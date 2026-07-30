#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

class Game : public IGame {
public:
	void start(GameEngine& engine) override;

    void update(F64 deltaTime) override;

private:
	F64 timeElapsed;

	Vector<GameObject> apps;
};
