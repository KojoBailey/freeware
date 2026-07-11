#pragma once

#include "Entity.hpp"

using ComponentIndex = Usz;

struct Position {
	F32 x, y;
};

template<typename ComponentType>
class ComponentStorage {
public:
	fn add(Entity entity, ComponentType component) -> Void
	{
		entityToComponentIndex[entity] = component.size();
		components.push_back(component);
		componentIndexToEntity.push_back(entity);
	}

	fn remove(Entity removedEntity) -> Void
	{
		ComponentIndex removedEntityComponentIndex = entityToComponentIndex[removedEntity];
		ComponentIndex lastComponentIndex = components.size() - 1;
		components[removedEntityComponentIndex] = components[lastComponentIndex];
		Entity movedEntity = componentIndexToEntity[lastComponentIndex];
		componentIndexToEntity[removedEntityComponentIndex] = movedEntity;
		entityToComponentIndex[movedEntity] = removedEntityComponentIndex;
		components.pop_back();
		componentIndexToEntity.pop_back();
		entityToComponentIndex.erase(removedEntity);
	}

	fn get(Entity targetEntity) -> ComponentType*
	{
		auto it = entityToComponentIndex.find(targetEntity);
		if (it == entityToComponentIndex.end()) {
			return nullptr;
		}
		return &components[it->second];
	}

	fn getStart() { return components.begin(); }
	fn getEnd() { return components.end(); }

private:
	Vector<ComponentType> components;
	Vector<Entity> componentIndexToEntity;
	HashMap<Entity, ComponentIndex> entityToComponentIndex;
};
