#pragma once

#include <string>
#include <stdexcept>


#define STR(X) STR_IMPL(X)
#define STR_IMPL(X) #X

namespace cppkit {
struct RuntimeCheckFailedError : public std::runtime_error {
    RuntimeCheckFailedError(const std::string &msg)
        : std::runtime_error(msg)
        {}
};
}

#define CHECK_MSG(cond, msg) do {                                           \
    if (!(cond)) {                                                          \
        throw cppkit::RuntimeCheckFailedError(                              \
            std::string("\n----------------------------------------")       \
                + "\n  CHECK FAILED:"                                       \
                + "\n  " + STR(cond) +                                      \
                + "\n    in function " + __FUNCTION__ +                     \
                + "\n    in file " + STR(__FILE__) + ":" + STR(__LINE__)    \
                + "\n  " + msg                                              \
                + "\n----------------------------------------"              \
        );                                                                  \
    }                                                                       \
} while(0)


#define CHECK(cond) CHECK_MSG(cond, "")
