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
		ComponentPool& pool;
		USz index;
		
		auto operator!=(this auto& self, const Iterator& other)
			-> Bool { return self.index != other.index; }

		void operator++(this auto& self)
		{
			++self.index;
		}

		auto operator*(this auto& self) -> Pair<GameObjectHandle&,TComponent&>
		{
			return {self.pool.handleByComponentIndex[self.index] , self.pool.components[self.index]};
		}
	};

public:
	// WARN: Does not account for allocation failure.
	auto emplace(this auto& self, GameObjectHandle handle , TComponent component) -> TComponent&
	{
		self.handleByComponentIndex.push_back(handle);
		USz newComponentIndex = self.components | pushAndGetIndex(std::move(component));
		self.componentIndexByHandle[handle.key] = newComponentIndex;
		return self.components[newComponentIndex];
	}
	
	auto get(this auto& self, GameObjectHandle handle) -> Maybe<TComponent&>
	{
		return (self.componentIndexByHandle | lookup(handle.key))
			.transform([&](auto componentIndex) -> auto& { return self.components[componentIndex]; });
	}
	
	auto has(this const auto& self, GameObjectHandle handle) -> Bool
	{
		return self.componentIndexByHandle.contains(handle.key);
	}

	void remove(this auto& self, GameObjectHandle handle)
	{
		USz removalIndex = self.componentIndexByHandle.at(handle.key);
		USz componentToMoveIndex = self.components.size() - 1;
		self.components[removalIndex] = std::move( self.components[componentToMoveIndex]);
		auto movedComponentHandle = self.handleByComponentIndex[componentToMoveIndex];
		self.handleByComponentIndex[removalIndex] = movedComponentHandle;
		self.componentIndexByHandle[movedComponentHandle.key] = removalIndex;
		self.components.pop_back();
	}
	
	auto begin(this auto& self)
		-> Iterator { return {self,0}; }

	auto end(this auto& self)
		-> Iterator { return {self,self.components.size()}; }

private:
	Vector<TComponent> components;
	Vector<GameObjectHandle> handleByComponentIndex;
	HashMap<U32,USz> componentIndexByHandle;
};
