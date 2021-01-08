#ifndef DOUBLE_PENDULUM_HPP
#define DOUBLE_PENDULUM_HPP

#include <utility>
#include <cmath>

namespace dp {

    double g  = 9.81;
    double dt = 0.005;

    struct state {
        std::pair<double, double> theta;
        std::pair<double, double> omega;
    };

    std::pair<double, double> operator+(const std::pair<double, double>& p1, const std::pair<double, double>& p2) noexcept {
        return {
            p1.first  + p2.first,
            p1.second + p2.second
        };
    }

    std::pair<double, double> operator*(const double d, const std::pair<double, double>& p) noexcept {
        return {
            d * p.first,
            d * p.second
        };
    }

    state operator+(const state& s1, const state& s2) noexcept {
        return {
            s1.theta + s2.theta,
            s1.omega + s2.omega
        };
    }

    state operator*(const double d, const state& s) noexcept {
        return {
            d * s.theta,
            d * s.omega
        };
    }

    struct system {
        std::pair<double, double> mass;
        std::pair<double, double> length;
    };
}

#endif