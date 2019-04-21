#pragma once

#include <cstdio>
#include<string>


namespace cppkit {


///
/// @brief printf style formatter that returns std::string
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


///
/// @brief Generates tokens from a `std::string`
///
/// Example:
/// ```cpp
///     StringTokenGenerator tokens("a,b,c,", ',');
///     while (tokens.has_next()) {
///         std::string_view t = tokens.next()
///         ...
///     }
/// ```
///
//-------------------------------------
class StringTokenGenerator {
//-------------------------------------
private:
    void go_next_j_() {
        while ((j_ <= str_.size()) && (str_[j_] != sep_)) ++j_;
    }

    const std::string &str_;
    const char sep_;
    std::size_t i_ = 0;     /// token begin index
    std::size_t j_ = 0;     /// token end index

public:
    StringTokenGenerator(const std::string &s, const char &sep)
        : str_(s), sep_(sep)
    { go_next_j_(); }

    bool has_next() const {
        return i_ < str_.size();
    }

    std::string next() {
        const auto &x = str_.substr(i_, j_-i_);
        i_ = j_++ + 1;
        // printf("%d (%lu, %lu]  ", __LINE__, i_, j_);
        go_next_j_();
        return std::move(x);
    }
};


} // namespace cppkit
