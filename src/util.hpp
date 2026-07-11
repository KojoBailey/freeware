#pragma once

#include <cstdint>
#include <expected>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <unordered_map>

#define fn auto

using Void = void;

using U8  = std::uint8_t;
using U16 = std::uint16_t;
using U32 = std::uint32_t;
using U64 = std::uint64_t;
using I8  = std::int8_t;
using I16 = std::int16_t;
using I32 = std::int32_t;
using I64 = std::int64_t;
using Usz = std::size_t;
using F32 = float;
using F64 = double;

using String = std::string;

template<typename T>
using Result = std::expected<T, String>;

template<typename T>
using Vector = std::vector<T>;

template<typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

fn exitWithError()
{
	std::exit(1);
}

template<typename T>
fn unwrapOrExit(Result<T> maybe) -> T
{
	if (not maybe.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe.error());
		exitWithError();
	}
	return std::move(*maybe);
}
