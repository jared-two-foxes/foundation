#ifndef __FUNCTIONAL_HPP__
#define __FUNCTIONAL_HPP__

#include <algorithm>
#include <vector>

namespace foundation {

template <typename T, typename Function >
auto map( Function&& fn, std::vector<T > const & xs ) -> std::vector<decltype(fn(std::declval<T>()))> {
    using ReturnType = decltype(fn(std::declval<T>()));
    std::vector<ReturnType> out;
    //out.resize( xs.size() );
    for ( auto&& x : xs ) {
        out.push_back( fn( x ) );
    }
    return out;
}

template <typename T, typename Function >
T filter( Function&& fn, T const & xs ) {
    T out;
    for ( auto& op : xs ) {
        if ( fn( op ) ) {
            out.push_back( op );
        }
    }
    return out;
}


}

#endif // __FUNCTIONAL_HPP__
