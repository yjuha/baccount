#include "strmath.h"
#include "utils.h"
#include "basic_account.h"
#include <map>
#include <fstream>

void BasicAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nType: " << account_type;
    std::cout << "\nBalance: " << balance.cents.substr(0,balance.cents.length()-2) << "," << balance.cents.substr(balance.cents.length()-2,2) << " euros";
    std::cout << "\nDate created: " << objid.get_time_created() << std::endl;
}

std::string BasicAccount::getAccountId() {
    return objid.get_accountId();
}

bool BasicAccount::writeAccountDetailsToFile() {

    std::string id = objid.get_accountId();
    const std::string accountfile = "./accounts/" + id;
    std::ofstream outf(accountfile);

    if (!outf) {
        std::cerr << "Error: file could not opened for writing" << std::endl;
        return false;
    }

    outf << objid.get_accountId() << std::endl;
    outf << account_type << std::endl;
    outf << balance.cents << std::endl;
    outf << objid.get_time_created() << std::endl;

    return true;

}
