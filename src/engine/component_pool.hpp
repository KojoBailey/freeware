#pragma once

#include "pch.hpp"
#include "util.hpp"
#include "game_object_handle.hpp"

// NOTE: `ComponentPool<T>` is templated, and this is the best way to generically
// store different instantiations of it, since `ComponentPool` alone doesn't suffice fsr.
class IComponentPool {};

template<typename TComponent>
class ComponentPool : public IComponentPool {
private:
	struct Iterator {
		ComponentPool& self;
		USz index;
		
		auto operator!=(const Iterator& other)
			-> Bool { return this->index != other.index; }

		void operator++()
		{
			++this->index;
		}

		auto operator*() -> Pair<GameObjectHandle&,TComponent&>
		{
			return {self.handleByComponentIndex[this->index] , self.components[this->index]};
		}
	};

public:
	// WARN: Does not account for allocation failure.
	auto emplace(GameObjectHandle handle , TComponent component) -> TComponent&
	{
		this->handleByComponentIndex.push_back(handle);
		USz newComponentIndex = components | pushAndGetIndex(std::move(component));
		this->componentIndexByHandle[handle.key] = newComponentIndex;
		return this->components[newComponentIndex];
	}
	
	auto get(GameObjectHandle handle) -> Maybe<Ref<TComponent>>
	{
		auto iterator = this->componentIndexByHandle.find(handle.key);
		if (not wasFindSuccessful(iterator , this->componentIndexByHandle))
			return {};
		auto& [key,componentIndex] = *iterator;
		return this->components[componentIndex];
	}
	
	auto has(GameObjectHandle handle) const -> Bool
	{
		return this->componentIndexByHandle.contains(handle.key);
	}

	void remove(GameObjectHandle handle)
	{
		USz removalIndex = this->componentIndexByHandle.at(handle.key);
		USz componentToMoveIndex = this->components.size() - 1;
		this->components[removalIndex] = std::move( this->components[componentToMoveIndex]);
		auto movedComponentHandle = this->handleByComponentIndex[componentToMoveIndex];
		this->handleByComponentIndex[removalIndex] = movedComponentHandle;
		this->componentIndexByHandle[movedComponentHandle.key] = removalIndex;
		this->components.pop_back();
	}
	
	auto begin()
		-> Iterator { return {*this,0}; }

	auto end()
		-> Iterator { return {*this,this->components.size()}; }

private:
	Vector<TComponent> components;
	Vector<GameObjectHandle> handleByComponentIndex;
	HashMap<U32,USz> componentIndexByHandle;
};
