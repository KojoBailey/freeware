#pragma once

#include "pch.hpp"
#include "game_object_handle.hpp"

class IComponentPool {
public:
	virtual ~IComponentPool() = default;
};

template<typename TComponent>
class ComponentPool : public IComponentPool {
public:
	auto emplace(GameObjectHandle handle, TComponent component) -> TComponent&
	{
		USz newIndex = components.size();
		handleToComponent[handle.index] = newIndex;
		components.push_back(std::move(component));
		componentToHandle.push_back(handle);
		return components.back();
	}
	
	auto get(GameObjectHandle handle) -> TComponent*
	{
		auto it = handleToComponent.find(handle.index);
		return it != handleToComponent.end()
			? &components[it->second]
			: nullptr;
	}
	
	auto has(GameObjectHandle handle) -> bool
	{
		return handleToComponent.contains(handle.index);
	}

	void remove(GameObjectHandle handle)
	{
		USz targetIndex = handleToComponent.at(handle.index);
		USz lastElement = components.size() - 1;
		components[targetIndex] = std::move(components[lastElement]);
		auto newHandle = componentToHandle[lastElement];
		componentToHandle[targetIndex] = newHandle;
		handleToComponent[newHandle.index] = targetIndex;
		components.pop_back();
	}
	
	auto toIter()
	{
		struct Iterator {
			ComponentPool& pool;
			USz index;
			
			auto operator!=(const Iterator& other) -> Bool { return index != other.index; }
			void operator++() { ++index; }
			auto operator*()
			{
				return std::pair<GameObjectHandle&, TComponent&>(pool.componentToHandle[index], pool.components[index]);
			}
		};
		struct Range {
			ComponentPool& pool;
			auto begin() -> Iterator { return { pool, 0 }; }
			auto end() -> Iterator { return { pool, pool.components.size() }; }
		};
		return Range{ *this };
	}

private:
	Vector<TComponent> components;
	Vector<GameObjectHandle> componentToHandle;
	HashMap<U32, USz> handleToComponent;
};
