#pragma once

#include <type_traits>

template<typename ...LAMBDAS>
struct overload : LAMBDAS... { using LAMBDAS::operator()...;  };

template<typename ...Ts>
overload(Ts...) -> overload<std::remove_cvref_t<Ts>...>;

namespace constexpr_impl {
	[[nodiscard]] static constexpr bool is_digit(const char c) {
		return c <= '9' && c >= '0';
	}

	[[nodiscard]] static constexpr size_t stoi_impl(const char* str, size_t value = 0) {
		return *str ?
			is_digit(*str) ?
			stoi_impl(str + 1, static_cast<size_t>(*str - '0') + value * 10)
			: throw "compile-time-error: not a digit"
			: value;
	}

	[[nodiscard]] static constexpr auto stoi(const char* str) -> decltype(auto) {
		return stoi_impl(str);
	}
}