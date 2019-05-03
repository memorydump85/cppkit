#include <cmath>
#include <limits>
#include <type_traits>



namespace cppkit {

namespace mathx {

template<class R>
inline bool is_close(
    const R& a,
    const R& b,
    const R& eps = std::numeric_limits<R>::epsilon() )
{
    return std::abs(b - a) < eps;
}

template <class R>
R to_radians(const R& deg) {
    static_assert( std::is_floating_point<R>::value, "" );
    return deg * R(M_PI) / R(180);
}

template <class R>
R to_degrees(const R& rad) {
    static_assert( std::is_floating_point<R>::value, "" );
    return rad * R(180) / R(M_PI);
}

} // namespace mathx

} // namespace cppkit