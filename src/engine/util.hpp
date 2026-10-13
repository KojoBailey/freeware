#pragma once

#include "pch.hpp"

#include <concepts>

// PERF: Calculating the index *before* pushing back to the vector
// avoids calculating subtraction with `vector.size() - 1`.
template<typename T , typename U>
	requires std::constructible_from<T,U>
auto pushAndGetIndex(Vector<T>& vector , U&& item) -> USz
{
	USz lastIndex = vector.size();
	vector.emplace_back(std::forward<U>(item));
	return lastIndex;
}

template<typename T>
struct PushAndGetIndexClosure {
	T&& item;
};

template<typename T>
PushAndGetIndexClosure(T&&) -> PushAndGetIndexClosure<T>;

template<typename T>
auto pushAndGetIndex(T&& item) { return PushAndGetIndexClosure{std::forward<T>(item)}; }

template<typename T , typename U>
auto operator|(Vector<T>& vec , PushAndGetIndexClosure<U>&& obj)
	-> USz { return pushAndGetIndex(vec , std::forward<U>(obj.item)); }

template<typename Container , std::input_iterator Iterator>
auto wasFindSuccessful(Iterator iterator , const Container& container)
	-> Bool { return iterator != container.end(); }

template<typename TKey, typename TValue>
auto lookup(HashMap<TKey, TValue>& map, const TKey& targetKey) -> Maybe<TValue&>
{
	auto iterator = map.find(targetKey);
	if (not wasFindSuccessful(iterator , map))
		return std::nullopt;
	auto& [_,value] = *iterator;
	return value;
}

template<typename TKey>
struct LookupClosure {
	TKey&& targetKey;
};

template<typename TKey>
LookupClosure(TKey&&) -> LookupClosure<TKey>;

template<typename TKey>
auto lookup(TKey&& targetKey) { return LookupClosure{std::forward<TKey>(targetKey)}; }

template<typename TKey , typename TValue, typename T>
auto operator|(HashMap<TKey, TValue>& map , LookupClosure<T>&& obj)
	-> Maybe<TValue&> { return lookup(map , std::forward<T>(obj.targetKey)); }

enum class QuitStatus {
	ShouldQuit,
	ShouldNotQuit,
};
