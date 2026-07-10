#include "button.hpp"

#include "SDL3/Sprite.hpp"

#include <print>
#include <string>
#include <string_view>

class AppButton : public Button {
public:
	AppButton() = default;

	AppButton(std::string_view _id, Texture* texture)
		: id{_id}
	{
		sprite = Sprite{texture, { .size = {30.0f, 30.0f} }};
		sprite.setPos({200.0f, 660.0f});
	}

	auto getSprite() -> Sprite&
	{
		return sprite;
	}

	void onClicked()
	{
		std::println("[{}] Clicked!", id);
	}

private:
	Sprite sprite;
	std::string id;
};
