#include "../engine/engine.hpp"

class Game : public IGame {
public:
	void start(GameEngine& engine) override;
    void update(F32 deltaTime) override;
};
