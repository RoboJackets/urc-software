#ifndef MINI_CHECK_HPP_
#define MINI_CHECK_HPP_

// Dependency-free assertions so the tests build with only GTSAM + Eigen (no
// ROS, no gtest). Each test is a main() that returns non-zero on failure.

#include <cstdlib>
#include <iostream>

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            std::cerr << __FILE__ << ":" << __LINE__ << " CHECK failed: "       \
                      << #condition << std::endl;                               \
            std::exit(1);                                                       \
        }                                                                       \
    } while (0)

#define CHECK_NEAR(actual, expected, tolerance)                                 \
    do {                                                                        \
        const double a_ = (actual);                                             \
        const double e_ = (expected);                                           \
        if (!(std::abs(a_ - e_) <= (tolerance))) {                              \
            std::cerr << __FILE__ << ":" << __LINE__ << " CHECK_NEAR failed: "  \
                      << #actual << " = " << a_ << ", expected " << e_          \
                      << " +/- " << (tolerance) << std::endl;                   \
            std::exit(1);                                                       \
        }                                                                       \
    } while (0)

#endif
