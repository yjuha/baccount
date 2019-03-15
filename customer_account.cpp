#include "customer_account.h"

void CustomerAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.euros << " euros " << balance.cents << " cents";
    std::cout << "\nFirst name: " << firstname;
    std::cout << "\nLast name: " << lastname;
    std::cout << "\nDate created: " << objid.get_time_created();
}
