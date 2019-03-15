#include "enterprise_account.h"

void EnterpriseAccount::getAccountDetails() const {
    std::cout << "\nID " << account_id;
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.euros << " euros " << balance.cents << " cents";
    std::cout << "\nBusiness ID: " << business_id;
    std::cout << "\nCompany name: " << company_name << '\n'; 
}
