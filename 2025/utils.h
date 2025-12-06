#pragma once

#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> readLines(std::string fileName) {
	std::ifstream file(fileName);
	std::string str;
	std::vector<std::string> out;
	
	while (std::getline(file, str)) {
		out.emplace_back(str);
	}

	return out;
}