#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "banking.h"
//#include "utils.h"


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

/*    std::string token;
    std::string mycents;
    std::string helptext = "\nYour input ";
    int retval = collectToken(helptext, token);
    int retval2 = checkDepositAndCollectCents(token, mycents);
    std::cout << retval2 << " " << mycents << std::endl;
    return 0;*/
}
