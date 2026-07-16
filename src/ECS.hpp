#pragma once

#include "ComponentStorage.hpp"

class EntityComponentSystem {
public:
	fn createEntity()
	{
		return nextEntity++;
	}

private:
	Entity nextEntity;
	ComponentStorage<Position> positions;
};