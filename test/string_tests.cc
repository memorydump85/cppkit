#include <string_view>

#include "cppkit/string.hh"
#include "cppkit/test_framework.hh"



using namespace cppkit;
using StringViewTokenGenerator = TokenGenerator<std::string_view>;


DEFINE_TEST(strfmt_test) {
    const auto &result = strfmt("%s %d %3.1f", "abc", 1, 2.f);
    CHECK_MSG( result == "abc 1 2.0", result );
}


DEFINE_TEST(string_token_generator_test) {
    {
        StringTokenGenerator tokens("a-b-c", '-');
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
        StringTokenGenerator tokens("-a-b--c-", '-');
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
        StringTokenGenerator tokens("a", '-');
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );

        CHECK( false == tokens.has_next() );
    }
}


DEFINE_TEST(stringview_token_generator_test) {
    {
        StringViewTokenGenerator tokens("a-b-c", '-');
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
        StringViewTokenGenerator tokens("-a-b--c-", '-');
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
        StringViewTokenGenerator tokens("a", '-');
        CHECK( tokens.has_next() );

        std::string t;
        t = tokens.next();
        CHECK_MSG( t == "a", t );

        CHECK( false == tokens.has_next() );
    }
}
