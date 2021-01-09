#include "double_pendulum.hpp"

using namespace dp;

state derive(const state& st, const dp::system& ss) noexcept {
        const double delta = st.theta.second - st.theta.first;
        const double mass  = ss.mass.first + ss.mass.second;

        double s = sin(delta);
        double c = cos(delta);

        double denominator = mass * ss.length.first - 
            ss.mass.second * ss.length.first * c * c;

        state derivative{{st.omega.first, st.omega.second}, {0, 0}};

        derivative.omega.first 
            = ss.mass.second * ss.length.first * st.omega.first * st.omega.first
                * s * c
            + ss.mass.second * g * sin(st.theta.second) * c
            + ss.mass.second * ss.length.second * st.omega.second 
                * st.omega.second * s
            - mass * g * sin(st.theta.first);

        derivative.omega.first /= denominator;

        denominator *= ss.length.second / ss.length.first;           

        derivative.omega.second
            = - ss.mass.second * ss.length.second * st.omega.second
                * st.omega.second * s * c
            + mass * g * sin(st.theta.first) * c
            - mass * ss.length.first * st.omega.first * st.omega.first * s
            - mass * g * sin(st.theta.second);

        derivative.omega.second /= denominator;

        return derivative;
}

state rk4(const state& st, const dp::system& ss) noexcept {
        state dydx = derive(st, ss);
        state k1   = dt * dydx;
        state yt   = st + 0.5 * k1;
        
              dydx = derive(yt, ss);
        state k2   = dt * dydx;
              yt   = st + 0.5 * k2;

              dydx = derive(yt, ss);
        state k3   = dt * dydx;
              yt   = st + k3;

              dydx = derive(yt, ss);
        state k4   = dt * dydx;
        
        return 
            st + (1.0 / 6) * k1 + (1.0 / 3) * k2 + 
                 (1.0 / 3) * k3 + (1.0 / 6) * k4;
    }

state advance(const state& st, const dp::system& ss, double time) noexcept {
        double passed = 0.0;

        state ret = st;

        do {
            ret = rk4(ret, ss);
            passed += dt;
        } while (passed < time);

        return ret;
    }