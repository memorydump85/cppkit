#include "cppkit/rigidbody.hh"
#include "cppkit/mathx.hh"
#include "cppkit/test_framework.hh"



using namespace cppkit::mathx;

DEFINE_TEST(xyzrph_recover_test) {
    const auto T = xyzrph_to_matrix(+0.1f, -0.1f, +0.1f, -0.1f, +0.1f, -0.1f);
    const auto xyzrph = matrix_to_xyzrph(T);

    CHECK( is_close(xyzrph(0), +0.1f, 1e-6f) );
    CHECK( is_close(xyzrph(1), -0.1f, 1e-6f) );
    CHECK( is_close(xyzrph(2), +0.1f, 1e-6f) );
    CHECK( is_close(xyzrph(3), -0.1f, 1e-6f) );
    CHECK( is_close(xyzrph(4), +0.1f, 1e-6f) );
    CHECK( is_close(xyzrph(5), -0.1f, 1e-6f) );
}


DEFINE_TEST(xyzrph_inv_test) {
    const auto R = rotation_matrix(-0.1f, +0.1f, -0.1f);
    const auto Rinv = R.transpose();

    CHECK( is_close(R.determinant(), 1.f, 1e-6f) );
    CHECK( (R * Rinv).isIdentity() );

    const auto T = translation_matrix(+0.1f, -0.1f, +0.1f);
    const auto Tinv = translation_matrix(-0.1f, +0.1f, -0.1f);
    CHECK( (T * Tinv).isIdentity() );

    CHECK ( ((T * R) * (R.transpose() * T.inverse())).isIdentity() );
}
