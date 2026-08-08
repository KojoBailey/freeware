#include "../engine/engine.hpp"
#include "../engine/game_object.hpp"

enum class AppType {
	Vim,
	Paint,
};

class App {
public:
	static auto create(GameEngine& engine, AppType type, SharedPtr<Texture> texture) -> Result<App>;

	auto getType() const -> AppType;

	auto getSize() const -> Vec2<F32>;

	auto getPosition() const -> Vec2<F32>;
	void setPosition(Vec2<F32> position);
	
	void update(F64 deltaTime);

private:
	AppType type;
	GameObject object;

	F64 timeElapsed{0};
};
