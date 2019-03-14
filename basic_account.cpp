#include "strmath.h"
#include "utils.h"
#include "basic_account.h"
#include <map>

void BasicAccount::getAccountDetails() const {
    std::cout << "\n Account details" << std::endl;
    std::cout << "Account ID: " << account_id << "\n";
    std::cout << "Account type: " << account_type << "\n";
    std::cout << "Balance: " << balance.euros << " euros " << balance.cents << " cents" << "\n";
}
void BasicAccount::modifyBalance(std::string& op) {
    
    if (op.at(0) == 'd') {
        std::cout << "How much to decrease?" << std::endl;
    } else {
        std::cout << "How much to increase?" << std::endl;
    }

    std::string euros = collectEuros();
    std::string cents = collectCents();

    std::string mycents = euros + cents; // in cents

    std::string balcents;

    if (balance.cents.length() == 1)
        balcents = balance.euros + '0' + balance.cents;
    else
        balcents = balance.euros + balance.cents;
 

    if (op.at(0) == 'd') {
        //check that old balance is bigger or equal to amount_cents
        bool valid = strmath::compare(balcents, mycents);
        
        if (valid) {
        // decrease can be done
            std::string mycents_new = strmath::subtract(balcents, mycents);
            balance.euros = mycents_new.substr(0, mycents_new.length() - 2);
            balance.cents = mycents_new.substr(mycents_new.length() - 2, 2);
        
        } else {
            std::cout << "Account balance is lower than" 
                " the amount you would like to decrease." << std::endl;
        }

    } else {

        std::string mycents_new = strmath::add(balcents, mycents);
        balance.euros = mycents_new.substr(0, mycents_new.length() - 2);
        balance.cents = mycents_new.substr(mycents_new.length() - 2, 2);
    }

}
