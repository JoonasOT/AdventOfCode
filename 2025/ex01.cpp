#include "ex01.h"

#include <format>
#include <algorithm>
#include <ranges>

#include "constexpr_utils.h"

struct Acc {
	size_t count = 0;
	int pos = 50;
};

[[nodiscard]] static constexpr int parseRow(const std::string_view row) {
	if (row.size() < 2) {
		throw std::logic_error("Row had less than two chars!!!");
	}
	const int turns = constexpr_impl::stoi(row.data() + 1);
	switch (*row.cbegin())
	{
	case 'L':
		return -turns;
	case 'R':
		return turns;
	default:
		throw std::logic_error(std::format("Invalid turn direction ({})!!", *row.cbegin()));
	}
}

[[nodiscard]] static constexpr int clamp(const int& i) {
	return i < 0 ? i + 100 : i % 100;
}

typedef size_t(*CountingStrategy)(bool endedAtZero, size_t revolutions);

template<typename T>
[[nodiscard]] static consteval CountingStrategy getStrategy() {
	return overload(
		[](const Simple&) consteval {
			return [](bool endedAtZero, size_t) constexpr { return static_cast<size_t>(endedAtZero); };
		},
		[](const Advanced&) consteval {
			return [](bool, size_t revolutions) constexpr { return revolutions; };
		}
	).operator()(T{});
}

typedef size_t(*CountingStrategy)(bool endedAtZero, size_t revolutions);

template<CountingStrategy strategy>
[[nodiscard]] static Acc accumulate(const Acc& acc, const int& turn) {
	const auto unclamped = acc.pos + turn % 100, clamped = clamp(unclamped);
	const auto revs = static_cast<size_t>(abs(turn) / 100);
	const auto edgeCase = ((clamped == 0 && abs(clamped) % 100 == 0) || (clamped != unclamped && acc.pos != 0));

	const auto newCount = acc.count + strategy(clamped == 0, edgeCase + revs);

	return Acc{
		.count = newCount,
		.pos = clamped
	};
}

template<>
size_t Ex01::solve<Simple>(const std::vector<std::string>& lines) {
	return std::ranges::fold_left(
		lines | std::ranges::views::transform(parseRow),
		Acc{},
		accumulate<getStrategy<Simple>()>
	).count;
}

template<>
size_t Ex01::solve<Advanced>(const std::vector<std::string>& lines) {
	return std::ranges::fold_left(
		lines | std::ranges::views::transform(parseRow),
		Acc{},
		accumulate<getStrategy<Advanced>()>
	).count;
}
