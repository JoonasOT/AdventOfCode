#pragma once

#include "common.h"

namespace Ex01 {
	template<section_type section>
	size_t solve(const std::vector<std::string>&);
	template<>
	size_t solve<Simple>(const std::vector<std::string>&);
	template<>
	size_t solve<Advanced>(const std::vector<std::string>&);
}

