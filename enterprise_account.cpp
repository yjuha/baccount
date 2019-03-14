#include "enterprise_account.h"

void EnterpriseAccount::getAccountDetails() const {
    std::cout << "\n ##### Account details" << std::endl;
    std::cout << "- Account ID: " << account_id << "\n";
    std::cout << "- Account type: " << account_type << "\n";
    std::cout << "- Balance: " << balance.euros << " euros " << balance.cents << " cents" << "\n";
    std::cout << "- Business ID: " << business_id << "\n";
    std::cout << "- Company name: " << company_name << "\n"; 
}
