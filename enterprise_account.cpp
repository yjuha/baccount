#include "enterprise_account.h"

void EnterpriseAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.euros << " euros " << balance.cents << " cents";
    std::cout << "\nBusiness ID: " << business_id;
    std::cout << "\nCompany name: " << company_name; 
    std::cout << "\nDate created: " << objid.get_time_created();
}
