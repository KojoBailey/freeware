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
struct _PushAndGetIndex {
	T&& item;
};

template<typename T>
_PushAndGetIndex(T&&) -> _PushAndGetIndex<T>;

template<typename T>
auto pushAndGetIndex(T&& item) { return _PushAndGetIndex{std::forward<T>(item)}; }

template<typename T , typename U>
auto operator|(Vector<T>& vec , _PushAndGetIndex<U>&& obj)
	-> USz { return pushAndGetIndex(vec , std::forward<U>(obj.item)); }

template<typename Container , std::input_iterator Iterator>
auto wasFindSuccessful(Iterator iterator , const Container& container)
	-> Bool { return iterator != container.end(); }

enum class QuitStatus {
	ShouldQuit,
	ShouldNotQuit,
};
