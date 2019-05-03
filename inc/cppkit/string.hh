#pragma once

#include <cstdio>
#include <string>

#include "validation_macros.h"


namespace cppkit {


/// `printf` style formatter that returns `std::string`
///
template<typename ... Args>
std::string strfmt(
    const std::string& format,
    Args ... args )
{
    // Estimate number of chars; Don't forget the NUL at the end
    const std::size_t &NBUF = snprintf( nullptr, 0, format.c_str(), args ... ) + 1;

    char buf[NBUF] = {}; 
    snprintf( buf, NBUF, format.c_str(), args ... );
    return std::string( buf, buf + NBUF - 1 /* leave out NUL */ );
}


/// Generate tokens from a `std::string`
///
/// Example:
/// ```cpp
///     StringTokenGenerator tokens("a,b,c,", ',');
///     while (tokens.has_next()) {
///         auto t = tokens.next();
///         ...
///     }
/// ```
/// or
/// ```cpp
///     StringTokenGenerator tokens("a,b,c", ',');
///     for(; tokens.has_next(); tokens.next()) {
///         process_token(tokens.peek());
//      }
/// ```
///
template<class S>
//-------------------------------------
class TokenGenerator {
//-------------------------------------
private:
    void go_next_j_() {
        while ((j_ < str_.size()) && (str_[j_] != sep_)) ++j_;
    }

    const S str_;
    const char sep_;
    std::size_t i_ = 0;     /// token begin index
    std::size_t j_ = 0;     /// token end index

public:
    TokenGenerator(const S &s, const char &sep)
        : str_(s)
        , sep_(sep)
        { go_next_j_(); }

    bool has_next() const
        { return i_ < str_.size(); }

    S peek() const {
        CHECK( (i_ <= str_.size()) && (j_ <= str_.size()) );
        return std::move(str_.substr(i_, j_-i_));
    }

    S next() {
        const auto &x = peek();
        i_ = j_++ + 1;
        go_next_j_();
        return std::move(x);
    }
};

using StringTokenGenerator = TokenGenerator<std::string>;

// Alternative:
// using StringViewTokenGenerator = TokenGenerator<std::string_view>;


} // namespace cppkit
