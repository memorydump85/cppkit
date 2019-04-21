#pragma once

#include <stdexcept>


#define STR(X) STR_IMPL(X)
#define STR_IMPL(X) #X

#define CHECK_MSG(cond, msg) do {                                           \
    if (!(cond)) {                                                          \
        throw std::runtime_error(                                           \
            std::string("\n----------------------------------------")       \
                + "\n  CHECK FAILED:"                                       \
                + "\n    in " + __FUNCTION__ + " at line " + STR(__LINE__)  \
                + "\n    " + STR(cond) + " FAILED"                          \
                + "\n    : " + msg                                          \
                + "\n----------------------------------------"              \
        );                                                                  \
    }                                                                       \
} while(0)


#define CHECK(cond) CHECK_MSG(cond, "")
