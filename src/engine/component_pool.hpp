#pragma once

#include "pch.hpp"
#include "game_object_handle.hpp"

// PERF: Calculating the index *before* pushing back to the vector
// avoids calculating subtraction with `vector.size() - 1`.
template<typename T>
auto pushAndGetIndex(Vector<T>& vector , const T& item) -> USz
{
	USz lastIndex = vector.size();
	vector.push_back(std::move(item));
	return lastIndex;
}

template<typename Container , std::input_iterator Iterator>
auto wasFindSuccessful(Iterator iterator , const Container& container)
	-> Bool { return iterator != container.end(); }

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
		USz newComponentIndex = pushAndGetIndex(components, std::move(component));
		this->componentIndexByHandle[handle.key] = newComponentIndex;
		return this->components[newComponentIndex];
	}
	
	auto get(GameObjectHandle handle) -> Maybe<Ref<TComponent>>
	{
		// PERF: `unordered_map::at` throws an exception on no find which is costly.
		// Hence, iterators must be used explicitly, even though the key is unimportant.
		// NOTE: This would be cleaner if the STL had an `unordered_map::maybe_at` method
		// that returned an `optional<T&>`.
		auto iterator = this->componentIndexByHandle.find(handle.key);
		if (not wasFindSuccessful(iterator , this->componentIndexByHandle))
			return {};
		auto& [key,componentIndex] = *iterator;
		return this->components[componentIndex];
	}
	
	auto has(GameObjectHandle handle) -> Bool
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
