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

	void changeY(F32 offset);
	
	void update(F64 deltaTime);

private:
	AppType type;
	GameObject object;

	F64 timeElapsed{0};
};
