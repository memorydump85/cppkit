#pragma once

#include <Eigen/Dense>
#include <cmath>



namespace cppkit {

namespace mathx {

using std::cos;
using std::sin;
using std::atan2;
using std::sqrt;


static inline
Eigen::Matrix4f translate_(float x, float y, float z) {
    Eigen::Matrix4f r;
    r << 1.,  0.,  0.,  x,
         0.,  1.,  0.,  y,
         0.,  0.,  1.,  z,
         0.,  0.,  0.,  1.   ;
    return r;
}

static inline
Eigen::Matrix4f rotx_(float t) {
    Eigen::Matrix4f r;
    r << 1.,      0.,      0.,  0.,
         0.,  cos(t), -sin(t),  0.,
         0.,  sin(t),  cos(t),  0.,
         0.,      0.,      0.,  1.   ;
    return r;
}

static inline
Eigen::Matrix4f roty_(float t) {
    Eigen::Matrix4f r;
    r << cos(t),  0.,  sin(t),  0.,
           0.,    1.,    0.,    0.,
        -sin(t),  0.,  cos(t),  0.,
           0.,    0.,    0.,    1.   ;
    return r;
}

static inline
Eigen::Matrix4f rotz_(float t) {
    Eigen::Matrix4f r;
    r << cos(t), -sin(t),  0.,   0.,
         sin(t),  cos(t),  0.,   0.,
             0.,      0.,  1.,   0.,
             0.,      0.,  0.,   1.  ;
    return r;
}

inline
Eigen::Matrix4f xyzrph_to_matrix(float x, float y, float z, float r, float p, float h) {
    return translate_(x, y, z) * rotz_(h) * roty_(p) * rotx_(r);
}

inline
auto matrix_to_xyzrph(const Eigen::Matrix4f &M) {
    Eigen::Matrix<float, 6, 1> r;
    r << M(0, 3),
         M(1, 3),
         M(2, 3),
         atan2(M(2, 1), M(2, 2)),
         atan2(-M(2, 0), sqrt(M(0, 0)*M(0, 0) + M(1, 0)*M(1, 0))),
         atan2(M(1, 0), M(0, 0));
    return r;
}

inline
auto xyzrph_to_matrix(const Eigen::Vector3f &xyz, const Eigen::Vector3f &rph) {
    return xyzrph_to_matrix(xyz(0), xyz(1), xyz(2), rph(0), rph(1), rph(2));
}

inline
auto translation_matrix(float x, float y, float z) {
    return xyzrph_to_matrix(x, y, z, 0, 0, 0);
}

inline
auto rotation_matrix(float r, float p, float h) {
    return xyzrph_to_matrix(0, 0, 0, r, p, h);
} 


} // namespace mathx

} // namespace cppkit