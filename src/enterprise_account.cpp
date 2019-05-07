#include "enterprise_account.h"

void EnterpriseAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.cents.substr(0,balance.cents.length()-2) << "," << balance.cents.substr(balance.cents.length()-2,2) << " euros";
 
    std::cout << "\nBusiness ID: " << business_id;
    std::cout << "\nCompany name: " << company_name;
    std::cout << "\nDate modified: " << objid.get_time_modified(); 
    std::cout << "\nDate created: " << objid.get_time_created();
}

bool EnterpriseAccount::writeAccountDetailsToFile() {

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
    outf << business_id << std::endl;
    outf << company_name << std::endl;
    outf << objid.get_time_modified();
    outf << objid.get_time_created() << std::endl;

    return true;

}
