
#include <greeter.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string name{"teddy"};
    greeter::Greeter greeter(name);
    std::cout << greeter.greet(greeter::LanguageCode::EN) << std::endl;
    return 0;
}