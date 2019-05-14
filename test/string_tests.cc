#include <string_view>

#include "cppkit/string.hh"
#include "cppkit/test_framework.hh"



using namespace cppkit;
using StringViewTokenGenerator = TokenGenerator<std::string_view>;


DEFINE_TEST(strfmt_test) {
    const auto &result = strfmt("%s %d %3.1f", "abc", 1, 2.f);
    CHECK_MSG( result == "abc 1 2.0", result );
}


template <class T>
void generic_token_generator_test_() {
    {
        T tokens("a-b-c", '-');
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );
        t = tokens.next();
        CHECK_MSG( t == "b", t );
        t = tokens.next();
        CHECK_MSG( t == "c", t );

        CHECK( false == tokens.has_next() );
    }
    {
        T tokens("-a-b--c-", '-');
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "", t );
        t = tokens.next();
        CHECK_MSG( t == "a", t );
        t = tokens.next();
        CHECK_MSG( t == "b", t );
        t = tokens.next();
        CHECK_MSG( t == "", t );
        t = tokens.next();
        CHECK_MSG( t == "c", t );
        t = tokens.next();
        CHECK_MSG( t == "", t );

        CHECK( false == tokens.has_next() );
    }
    {
        T tokens("a", '-');
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );

        CHECK( false == tokens.has_next() );
    }
    //
    // Ignore consecutive
    //
    {
        T tokens("a-b-c", '-', /*ignore_consecutive*/ true);
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );
        t = tokens.next();
        CHECK_MSG( t == "b", t );
        t = tokens.next();
        CHECK_MSG( t == "c", t );

        CHECK( false == tokens.has_next() );
    }
    {
        T tokens("-a-b--c-", '-', /*ignore_consecutive*/ true);
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "", t );
        t = tokens.next();
        CHECK_MSG( t == "a", t );
        t = tokens.next();
        CHECK_MSG( t == "b", t );
        t = tokens.next();
        CHECK_MSG( t == "c", t );
        t = tokens.next();
        CHECK_MSG( t == "", t );

        CHECK( false == tokens.has_next() );
    }
    {
        T tokens("a", '-', /*ignore_consecutive*/ true);
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );

        CHECK( false == tokens.has_next() );
    }
}


DEFINE_TEST(string_token_generator_test) {
    generic_token_generator_test_<StringTokenGenerator>();
}


DEFINE_TEST(stringview_token_generator_test) {
    generic_token_generator_test_<StringViewTokenGenerator>();
}
