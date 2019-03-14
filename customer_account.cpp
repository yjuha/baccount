#include "customer_account.h"

void CustomerAccount::getAccountDetails() const {
    std::cout << "\n ##### Account details" << std::endl;
    std::cout << "- Account ID: " << account_id << "\n";
    std::cout << "- Account type: " << account_type << "\n";
    std::cout << "- Balance: " << balance.euros << " euros " << balance.cents << " cents" << "\n";
    std::cout << "- First name: " << firstname << "\n";
    std::cout << "- Last name: " << lastname << "\n";
}
