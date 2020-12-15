#include <random>
#include <iostream>
#include <fstream>
#include "double_pendulum.hpp"


int main(){
    int steps = 100;

    std::ofstream file;
    file.open("data.txt");

    dp::state st{{3.14, 1.5}, {0, 0}};
    dp::system ss{{1, 1}, {2, 3}};

    int k = 0;

    while (k < steps){
        k++;
        std::cout << "1st: " << st.theta.first << "; 2nd: " << st.theta.second << std::endl;
        file << st.theta.first << ";" << st.theta.second << std::endl;
        st = dp::advance(st, ss, 0.2);
    }

    file.close();

    return 0;
}