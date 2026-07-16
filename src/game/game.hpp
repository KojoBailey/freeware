#include "../engine/engine.hpp"

class Game : public IGame {
public:
	void start(GameEngine& engine) override {}

    void update(F32 deltaTime) override {}

    void render(Renderer& renderer) override {
		renderer.setDrawColor(200, 50, 50);
		SDL_FRect sdlFRect = {
			.x = 20,
			.y = 20,
			.w = 100,
			.h = 100,
		};
		SDL_RenderFillRect(renderer.get(), &sdlFRect);
	}
};