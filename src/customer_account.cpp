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
