#ifndef FOUNDATION_STRING_HELPER_HPP__
#define FOUNDATION_STRING_HELPER_HPP__

#include <iomanip>
#include <sstream>
#include <string>

namespace ui
{


// template <typename T >
// std::string cast( T const& o );
//
// inline std::string cast( float const& o ) {
//     std::stringstream stream;
//     stream << std::fixed << std::setprecision(2) << o;
//     return stream.str();
// }
//
// inline std::string cast( std::string const& o ) {
//     return std::string( o );
// }

inline auto toString(std::string const& x) -> std::string {
	return x;
}

template <class T>
auto toString(T const& x) ->decltype(std::to_string(x)) {
	return std::to_string(x);
}


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

template <class T, class F>
auto map(T const& data, F const& f) {
  std::vector<decltype(f(data[0]))> result(data.size());
  std::transform(
  	data.begin(), data.end(),
  	result.begin(),
  	f);
  return result;
}

inline std::string repeat(unsigned n, std::string const& s) {
	std::string result = "";
	for (unsigned i = 0; i < n; ++i) {
		result += s;
	}
	return result;
}


inline std::vector<std::string> split( std::string str, std::string token ) {
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


}

#endif // string_helper
