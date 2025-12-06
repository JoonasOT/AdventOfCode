#pragma once

#include <string>
#include <vector>
#include <concepts>

struct ExSection {
    using section_type = std::true_type;
};

struct Simple : ExSection {};
struct Advanced : ExSection {};

template<typename T>
concept section_type = std::is_same_v<T, Simple> || std::is_same_v<T, Advanced>;
