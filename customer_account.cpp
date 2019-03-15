#include "customer_account.h"

void CustomerAccount::getAccountDetails() const {
    std::cout << "\nID " << account_id;
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.euros << " euros " << balance.cents << " cents";
    std::cout << "\nFirst name: " << firstname;
    std::cout << "\nLast name: " << lastname << '\n';
}
