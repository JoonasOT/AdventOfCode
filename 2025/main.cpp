#include <print>

#include "ex01.h"
#include "utils.h"


int main(void) {
	const auto file = readLines("./input/1.txt");

	std::println("{}", Ex01::solve<Advanced>(file));
}