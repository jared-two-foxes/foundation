#ifndef FOUNDATION_STRING_SPLIT_HPP__
#define FOUNDATION_STRING_SPLIT_HPP__

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


namespace foundation
{

inline std::vector<std::string > split(std::string const& str, const std::string& delimiter = "\n") {
	std::vector<std::string > tokens;

	auto start = 0U;
	auto end = str.find(delimiter);
	while (end != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + delimiter.size();
		end = str.find(delimiter, start);
	}

	if (start != str.size()) {
		tokens.push_back(str.substr(start, str.size() - start));
	}

	return tokens;
}

}

#endif // FOUNDATION_STRING_SPLIT_HPP__
