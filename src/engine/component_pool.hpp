#pragma once

#include "pch.hpp"
#include "game_object_handle.hpp"

// NOTE: `ComponentPool<T>` is templated, and this is the best way to generically
// store different instantiations of it, since `ComponentPool` alone doesn't suffice fsr.
class IComponentPool {};

template<typename TComponent>
class ComponentPool : public IComponentPool {
public:
	// WARN: Does not account for allocation failure.
	auto emplace(
		GameObjectHandle handle,
		TComponent component
	) -> TComponent&
	{
		registerHandle(handle);
		USz newComponentIndex = pushBackAndGetLastIndex(components, std::move(component));
		componentIndexByHandle[handle.key] = newComponentIndex;
		return components[newComponentIndex];
	}
	
	auto get(GameObjectHandle handle) -> Maybe<Ref<TComponent>>
	{
		// PERF: `unordered_map::at` throws an exception on no find which is costly.
		// Hence, iterators must be used explicitly, even though the key is unimportant.
		// NOTE: This would be cleaner if the STL had an `unordered_map::maybe_at` method
		// that returned an `optional<T&>`.
		auto iterator = componentIndexByHandle.find(handle.key);
		if (not wasFindSuccessful(iterator, componentIndexByHandle))
			return {};
		auto& [key, componentIndex] = *iterator;
		return components[componentIndex];
	}
	
	auto has(GameObjectHandle handle) -> Bool
	{
		return componentIndexByHandle.contains(handle.key);
	}

	void remove(GameObjectHandle handle)
	{
		USz removalIndex = componentIndexByHandle.at(handle.key);
		USz componentToMoveIndex = components.size() - 1;
		components[removalIndex] = std::move(components[componentToMoveIndex]);
		auto movedComponentHandle = handleByComponentIndex[componentToMoveIndex];
		handleByComponentIndex[removalIndex] = movedComponentHandle;
		componentIndexByHandle[movedComponentHandle.key] = removalIndex;
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
				return Pair<GameObjectHandle&, TComponent&>(
					pool.handleByComponentIndex[index], pool.components[index]);
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
	Vector<GameObjectHandle> handleByComponentIndex;
	HashMap<U32,USz> componentIndexByHandle;

	// PERF: Calculating the index *before* pushing back to the vector
	// avoids calculating subtraction with `vector.size() - 1`.
	template<typename T>
	auto pushBackAndGetLastIndex(
		Vector<T>& vector,
		const T& item
	) -> USz
	{
		USz lastIndex = vector.size();
		vector.push_back(std::move(item));
		return lastIndex;
	}

	void registerHandle(GameObjectHandle handle)
	{
		handleByComponentIndex.push_back(handle);
	}

	template<typename Container, std::input_iterator Iterator>
	auto wasFindSuccessful(
		Iterator iterator,
		const Container& container
	) -> Bool
	{
		return iterator != container.end();
	}
};
