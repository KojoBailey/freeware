#pragma once

#include "pch.hpp"

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

enum class QuitStatus {
	ShouldQuit,
	ShouldNotQuit,
};
