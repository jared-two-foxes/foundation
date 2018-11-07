#ifndef FOUNDATION_STRING_HELPER_HPP__
#define FOUNDATION_STRING_HELPER_HPP__

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


namespace foundation
{

inline auto toString( float const& f ) -> std::string {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << f;
	return stream.str();
}

inline auto toString( std::string const& x ) -> std::string {
	return x;
}

template <class T>
auto toString( T const& x ) ->decltype(std::to_string(x)) {
	return std::to_string( x );
}

inline std::string repeat(unsigned n, std::string const& s) {
	std::string result = "";
	for (unsigned i = 0; i < n; ++i) {
		result += s;
	}
	return result;
}

}

#endif // string_helper
