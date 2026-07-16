#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

class Game : public IGame {
public:
	void start(GameEngine& engine) override {
		auto gameObject = engine.createGameObject();
		auto& rectRenderer = gameObject.addComponent<RectRenderer>();
		rectRenderer.size = { .x = 100, .y = 100 };
		rectRenderer.color = { .red = 200, .green = 50, .blue = 50 };
	}

    void update(F32 deltaTime) override {}
};