#include "customer_account.h"

/*!
 * This method simply prints the details of the given customer account
 * to screen.
 *
 */
void CustomerAccount::getAccountDetails() {
    std::cout << "\nID " << objid.get_accountId();
    std::cout << "\nAccount type: " << account_type;
    std::cout << "\nBalance: " << balance.cents.substr(0,balance.cents.length()-2) << "," << balance.cents.substr(balance.cents.length()-2,2) << " euros";
 
    std::cout << "\nFirst name: " << firstname;
    std::cout << "\nLast name: " << lastname;
    std::cout << "\nDate created: " << objid.get_time_created();
}

bool CustomerAccount::writeAccountDetailsToFile() {

    std::string id = objid.get_accountId();
    const std::string accountfile = "./accounts/" + id;
    std::ofstream outf(accountfile);

    if (!outf) {
        std::cerr << "Error: file could not opened for writing" << std::endl;
        return false;
    }

    outf << objid.get_accountId() << std::endl;     // Id
    outf << account_type << std::endl;              // account type
    outf << balance.cents << std::endl;             // balance
    outf << firstname << std::endl;                 // first name
    outf << lastname << std::endl;                  // last name
    outf << objid.get_time_created() << std::endl;  // time created

    return true;

}
