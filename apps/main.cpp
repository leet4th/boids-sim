#include <Eigen/Dense>
#include <greeter.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    // using own lib
    std::string name{"teddy"};
    greeter::Greeter greeter(name);
    std::cout << greeter.greet(greeter::LanguageCode::EN) << std::endl;

    // using eigen
    Eigen::Matrix2d A;
    A << 1, 2, 3, 4;

    Eigen::Matrix2d B;
    B << 5, 6, 7, 8;

    Eigen::Matrix2d C = A + B;
    std::cout << "Matrix A + B:\n" << C << "\n\n";

    return 0;
}