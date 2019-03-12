#include <iostream>
#include <string>
#include <string.h>

int main(int argc, char** argv) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        std::cout << "This is the help for " << argv[0] << "\n";
        return 0;
    }
    
    std::string input_str;

    do 
    {
        std::cout << "Enter character: " << std::endl;
        std::getline(std::cin, input_str);

        if (input_str.length() > 1) {
            std::cout << "Only one character accepted\n";
        } else {
            std::cout << "Your input length is one character\n";
        }
    
    } 
    while(input_str.at(0)!='q');
    std::cout << "Bye bye!\n";

    return 0;
}
