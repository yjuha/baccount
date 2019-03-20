#include <iostream>
#include <cstring>

#include "banking.h"

int main(int argc, char** argv) {

    // help
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            std::cout << "This is the help for " << argv[0] << "\n";
            return 0;
        }
    }

    Banking instance;

    return instance.execute();

}
