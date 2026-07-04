#ifndef MAIN_UTIL_HPP
#define MAIN_UTIL_HPP

#include <expected>
#include <iostream>
#include <print>
#include <string>

enum MainResult : int {
	Ok = 0,
	Error = 1,
};

template<typename T>
auto unwrapOrExit(std::expected<T, std::string> maybe) -> T
{
	if (not maybe.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe.error());
		std::exit(MainResult::Error);
	}
	return std::move(*maybe);
}

#endif
