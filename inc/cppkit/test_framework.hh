#pragma once

#include "validation_macros.h"


/// Macro for defining unit-tests. Defines as a destructor-type function
/// that is automatically invoked `after` main exits.
///
/// `__attribute__ ((destructor))` is used instead of
/// `__attribute__ ((constructor))` because constructor-type functions
/// seem to be invoked before static variables are initialized.
///
#define DEFINE_TEST(FUNC)                               \
    __attribute__ ((destructor)) void FUNC()


/// Ensures that `code` throws an `exc_type` exception.
///
#define MUST_THROW(code, exc_type) do {                 \
    bool exception_thrown = false;                      \
    try {                                               \
        code;                                           \
    } catch(const exc_type& e) {                        \
        exception_thrown = true;                        \
    }                                                   \
    CHECK_MSG(exception_thrown, std::string("Did not throw required exception ") + STR(exc_type));  \
} while(0)
