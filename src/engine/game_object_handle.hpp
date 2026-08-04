#pragma once

#include "pch.hpp"

class GameObjectHandle {
public:
	U32 index;
	U32 generation = 0;

	void deregister()
	{
		// NOTE: An index of 0 signifies an empty game object.
		// Could use std::optional, but seems excessive.
		index = 0;
	}
};
