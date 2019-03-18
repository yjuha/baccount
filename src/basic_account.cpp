#include "strmath.h"
#include "utils.h"
#include "basic_account.h"
#include <map>

void BasicAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nType: " << account_type;
    std::cout << "\nBalance: " << balance.cents.substr(0,balance.cents.length()-2) << "," << balance.cents.substr(balance.cents.length()-2,2) << " euros";
    std::cout << "\nDate created: " << objid.get_time_created() << std::endl;
}

