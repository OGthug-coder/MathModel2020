#include <iostream>
#include <fstream>
#include <string>
#include "double_pendulum.cpp"


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
    bool calculations = true;

    while (calculations){
        while (k < steps){
            k++;
            std::cout << "1st: " << st.theta.first << "; 2nd: " << st.theta.second << std::endl;
            file << st.theta.first << ";" << st.theta.second << std::endl;
            st = advance(st, ss, 0.2);
        }

        std::cout << "Would you like to continue calculations? (y/n)" << std::endl;
        std::string command;
        std::cin >> command;
    
        if (command == "y"){
            std::cout << "How many additional steps would you like to execute?" << std::endl;
            int _steps;
            std::cin >> _steps;
            k = 0;
            steps = _steps;
            calculations = true;
        } else if (command == "n"){
            calculations = false;
        }
    }
    

    file.close();
    std::cout << "Finishing calculations" << std::endl;

    return 0;
}