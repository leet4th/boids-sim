
#include <greeter.hpp>


#include <string>
#include <iostream>

int main(int argc, char *argv[])
{

   std::string name{"lee"};
   greeter::Greeter greeter(name);
   std::cout << greeter.greet(greeter::LanguageCode::EN) << std::endl;
   return 0;
}