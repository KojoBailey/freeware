#pragma once

#include <cstdint>
#include <expected>
#include <memory>
#include <optional>
#include <print> // IWYU pragma: keep
#include <string>
#include <string_view>
#include <type_traits> // IWYU pragma: keep
#include <unordered_map>
#include <vector>

#define UNWRAP_OR_EXIT(expr) \
	({ \
		auto&& _maybe = (expr); \
		if (not _maybe.has_value()) { \
			std::println(stderr, "[ERROR] {}@{}: {}", __FILE__, __LINE__, _maybe.error()); \
			std::exit(1); \
		} \
		if constexpr (not std::is_void_v<typeof(_maybe)>) { \
			std::move(*_maybe); \
		} \
	})

using Nothing = void;
using Bool = bool;
using Char = char;
using CInt = int;
using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;
using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;
using USz = uintptr_t;
using ISz = ptrdiff_t;
using F32 = float;
using F64 = double;

using String = std::string;
using StringView = std::string_view;

template<typename T>
using Result = std::expected<T, String>;

template<typename T>
using Error = std::unexpected<T>;

template<typename T>
using Maybe = std::optional<T>;

template<typename T>
using Vector = std::vector<T>;

template<typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

template<typename T, typename D = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T, D>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
class Vec2 {
public:
	T x, y;
};

class RGB {
public:
	U8 red, green, blue;
};
