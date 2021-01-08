#include <random>
#include <iostream>
#include <fstream>
#include "double_pendulum.hpp"


dp::state derive(const dp::state& st, const dp::system& ss) noexcept {
        const double delta = st.theta.second - st.theta.first;
        const double mass  = ss.mass.first + ss.mass.second;

        double s = sin(delta);
        double c = cos(delta);

        double denominator = mass * ss.length.first - 
            ss.mass.second * ss.length.first * c * c;

        dp::state derivative{{st.omega.first, st.omega.second}, {0, 0}};

        derivative.omega.first 
            = ss.mass.second * ss.length.first * st.omega.first * st.omega.first
                * s * c
            + ss.mass.second * dp::g * sin(st.theta.second) * c
            + ss.mass.second * ss.length.second * st.omega.second 
                * st.omega.second * s
            - mass * dp::g * sin(st.theta.first);

        derivative.omega.first /= denominator;

        denominator *= ss.length.second / ss.length.first;           

        derivative.omega.second
            = - ss.mass.second * ss.length.second * st.omega.second
                * st.omega.second * s * c
            + mass * dp::g * sin(st.theta.first) * c
            - mass * ss.length.first * st.omega.first * st.omega.first * s
            - mass * dp::g * sin(st.theta.second);

        derivative.omega.second /= denominator;

        return derivative;
    }

    dp::state rk4(const dp::state& st, const dp::system& ss) noexcept {
        dp::state dydx = derive(st, ss);
        dp::state k1   = dp::dt * dydx;
        dp::state yt   = st + 0.5 * k1;
        
              dydx = derive(yt, ss);
        dp::state k2   = dp::dt * dydx;
              yt   = st + 0.5 * k2;

              dydx = derive(yt, ss);
        dp::state k3   = dp::dt * dydx;
              yt   = st + k3;

              dydx = derive(yt, ss);
        dp::state k4   = dp::dt * dydx;
        
        return 
            st + (1.0 / 6) * k1 + (1.0 / 3) * k2 + 
                 (1.0 / 3) * k3 + (1.0 / 6) * k4;
    }

    dp::state advance(const dp::state& st, const dp::system& ss, double time) noexcept {
        double passed = 0.0;

        dp::state ret = st;

        do {
            ret = rk4(ret, ss);
            passed += dp::dt;
        } while (passed < time);

        return ret;
    }

int main(){
    int steps;
    double m1, m2, l1, l2, theta1, theta2, omega1, omega2;

    std::cout << "Steps of integration:" << std::endl;
    std::cin >> steps;

    std::cout << "Masses m1 and m2:" << std::endl;
    std::cin >> m1 >> m2;

    std::cout << "Length l1 and l2:" << std::endl;
    std::cin >> l1 >> l2;

    std::cout << "Initial angle diviations theta1 and theta2:" << std::endl;
    std::cin >> theta1 >> theta2;

    std::cout << "Initial angular velocities:" << std::endl;
    std::cin >> omega1 >> omega2;

    std::ofstream file;
    file.open("data.txt");

    dp::state st{{theta1, theta2}, {omega1, omega2}};
    dp::system ss{{m1, m2}, {l1, l2}};

    int k = 0;

    while (k < steps){
        k++;
        // std::cout << "1st: " << st.theta.first << "; 2nd: " << st.theta.second << std::endl;
        file << st.theta.first << ";" << st.theta.second << std::endl;
        st = advance(st, ss, 0.2);
    }

    file.close();

    return 0;
}