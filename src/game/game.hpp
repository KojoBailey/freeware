#include "../engine/i_game.hpp"

class Game : public IGame {
public:
    void update(F32 deltaTime) override {}

    void render(Renderer& renderer) override {}
};