#include "banking.h"
#include "dbmanager.h"
#include "strmath.h"
#include "utils.h"
#include "basic_account.h"
#include "customer_account.h"
#include "enterprise_account.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>

void Banking::printheader() const {
    std::cout << "\n#########################################"
                 "\n############## BACCOUNT #################"
                 "\n#########################################\n";
}

void Banking::help() const {

    std::cout << "\n[MAIN MENU]" 
                    "\nOptions:" 
                    "\na - add account"
                    "\nr - remove account"
                    "\ni - deposit"
                    "\nd - withdrawal" 
                    "\ns - show account" 
                    "\nq - quit program\n";
    
    std::cout << "\nEnter your option (a/r/i/d/s/q) > ";
}
void Banking::help_addAccount() const {
     std::cout << "\n[ADD ACCOUNT]" 
                    "\nOptions:" 
                    "\nb - add basic account"
                    "\nc - add customer account"
                    "\ne - add enterprise account"
                    "\nq - return to main menu\n";
    
    std::cout << "\nEnter your option (b/c/e/q) > ";
}

void Banking::help_collectDeposit() const {
     std::cout << "\nNOTE: acceptable deposit formats:" 
                    "\nX -> X euros" 
                    "\nX, -> X euros"
                    "\n,X[X] -> X[X] cents (only two digits accepted after comma)"
                    "\n[ABC...]Y,X -> [ABC...]Y euros X cents (any number of digits accepted before comma)\n";
}
void Banking::help_collectAID() const {
     std::cout << "\nNOTE: account IDs must contain five (5) digits\n"; 
}
bool Banking::listAccounts() {
    std::cout << "\n[AVAILABLE ACCOUNTS (listed by ID)]" << std::endl;
    accountsMap_t::iterator it;

    if( accounts.size() == 0) {
        std::cout << "** DATABASE EMPTY **" << std::endl;
        return false;
    } else {
        for (it = accounts.begin(); it !=accounts.end(); ++it) {
            std::cout << it->first << std::endl;
        }
        std::cout << "\n";
        return true;
    }
}

int Banking::deposit(std::string& input_str) {
    accountsMap_t::iterator it = accounts.find(input_str);
    if (it != accounts.end()) { 
        std::cout << "\n[ACCOUNT ID: " << it->first << "]";
        bool cont_dowhile = false;
        (it->second)->getAccountDetails();
        std::string oldcents = (it->second)->get_cents();
        std::string newcents;
        std::string total;

        do
        {
            help_collectDeposit();
            std::string helptext = "\nType in euros";
            std::string input_str;

            if (collectToken(helptext, input_str) == -1) {
                return -2;
            }            
        
            if (checkDepositAndCollectCents(input_str, newcents) == -1) {
                std::cout << "\nError: Invalid format, try again.";
                cont_dowhile = true;
            } else {
                total = strmath::add(oldcents, newcents);  
                (it->second)->set_cents(total);
                cont_dowhile = false;
            }
        }
        while(cont_dowhile);
        (it->second)->set_timemodified(); 
        std::cout << "\n[ACCOUNT ID: " << it->first << "] UPDATED";
        (it->second)->getAccountDetails();
        return 0;
    } else {
        return -1;
    }
}

int Banking::decrease(std::string& input_str) {
    accountsMap_t::iterator it = accounts.find(input_str);
    if (it != accounts.end()) { 
        std::cout << "\n[ACCOUNT ID: " << it->first << "]";
        bool cont_dowhile = false;
        (it->second)->getAccountDetails();
        std::string oldcents = (it->second)->get_cents();
        std::string newcents;
        std::string total;
        if (oldcents.compare("0")!=0) {
        do
        {
            help_collectDeposit();
            std::string helptext = "\nType in euros";
            std::string input_str;

            if (collectToken(helptext, input_str) == -1) {
                return -2;
            }            
        
            if (checkDepositAndCollectCents(input_str, newcents) == -1) {
                std::cout << "\nError: Invalid format, try again.";
                cont_dowhile = true;
            } else {

                if (strmath::compare(oldcents, newcents)) {
                    total = strmath::subtract(oldcents, newcents);
                    (it->second)->set_cents(total);
                    cont_dowhile = false;
                } else {
                    cont_dowhile = true;
                    std::cout << "\nPlease, check the current balance:" << std::endl;
                    (it->second)->getAccountDetails();
                }
            }
        }
        while(cont_dowhile);
        (it->second)->set_timemodified();
        std::cout << "\n[ACCOUNT ID: " << it->first << "] UPDATED";
        (it->second)->getAccountDetails();} else {std::cout << "\nCurrent balance is 0 euros." << std::endl;}
        return 0;
    } else {
        return -1;
    }
}



int Banking::show(std::string& input_str) {
    accountsMap_t::iterator it = accounts.find(input_str);
    if (it != accounts.end()) { 
        std::cout << "\n[ACCOUNT ID: " << it->first << "]";
        (it->second)->getAccountDetails();
        return 0;
    } else {
        return -1;
    }
}

int Banking::remove(std::string& input_str) {
    accountsMap_t::iterator it = accounts.find(input_str);
    if (it != accounts.end()) {
        delete it->second;
        accounts.erase(it);
        dbmanager->removeAccountFromFile(it->first);
        std::cout << "\n[ACCOUNT ID: " << it->first << "] removed\n";
        return 0;
    } else {
        return -1;
    }
} 

void Banking::selectOperation(std::string& operation, int (Banking::*myop)(std::string&)) {
    bool cont_dowhile = false;

    if(listAccounts()) {
        do
        {
            help_collectAID();
            std::cout << "\n[ACCOUNT "<< operation  << "] (press 'q' to cancel)";
            std::cout << "\nType in account ID > ";
            std::string input_str;
            std::getline(std::cin, input_str);

            if ( input_str.empty() == 1 ) {
                cont_dowhile = true;
            } else if (input_str.length() == 1 ) {
                if (input_str.at(0) == 'q') {
                    cont_dowhile = false;
                } else {
                    cont_dowhile = true;
                    std::cerr << "\nError: Invalid Account ID" 
                        " - IDs can contain 5 chars and all of them must be numbers" << std::endl;
                }   
            } else if ( input_str.length() == 5 ) {
                if ( !containsOnlyDigits(input_str)) {
                    cont_dowhile = true;
                    std::cerr << "\nError: Invalid Account ID - IDs can contain only numbers" << std::endl;
                } else {

                    int retval = (this->*myop) (input_str);

                    if ( retval == -1 ) {
                        std::cerr << "\nError: Account ID " << input_str << " not found."; 
                        cont_dowhile = true;    
                    } else if ( retval == -2 ) {
                        std::cout << "\nProcedure cancelled";
                        cont_dowhile = false;
                    } else {
                        cont_dowhile = false;
                    }                    
                }                   
            } else {
                cont_dowhile = true;
                std::cerr << "\nError: Invalid Account ID - IDs are five (5) chars long" << std::endl;
            }
        }   
        while(cont_dowhile);
    }
}
bool Banking::collectAccountInfo(std::string atype, \
                                        std::string &account_id, \
                                        std::string &cents, \
                                        std::string &info1, \
                                        std::string &info2) {

    bool cont_dowhile = false;
    bool cancel = false;
    do
    {   
        std::cout << "\n[NEW ACCOUNT]";
        help_collectAID();
        std::string helptext = "\nType Account ID";
        std::string input_str;
        if (collectToken(helptext, input_str) == -1) {
            std::cout << "\nProcedure cancelled" << std::endl;
            cancel = true;
            break;
        }
        
        if (input_str.length() == 5 ) {
            if ( !containsOnlyDigits(input_str)) {
                cont_dowhile = true;
                std::cerr << "\nError: Invalid Account ID - IDs can contain only numbers" << std::endl;
            } else {
                accountsMap_t::iterator it = accounts.find(input_str);
                if (it != accounts.end()) {
                    cont_dowhile = true;
                    std::cout << "\nAccount ID" << input_str << " reserved, try new ID. " << std::endl;
                } else {
                    cont_dowhile = false;
                    account_id = input_str;
                    
                    do
                    {
                        help_collectDeposit();
                        std::string helptext = "\nDo initial deposit? (y/n)";
                        std::string input_chr;
                        if (collectToken(helptext, input_chr) == -1) {
                            std::cout << "\nProcedure cancelled" << std::endl;
                            cancel = true;
                            break;
                        }

                        if (input_chr.length() > 1 ) {
                            std::cerr << "Error: Unknown option" << std::endl;
                            cont_dowhile = true;
                        } else {
                            if (input_chr.at(0) == 'y') {
                                std::string helptext = "\nEnter sum in Euros";
                                std::string input_str;

                                if (collectToken(helptext, input_str) == -1) {
                                    std::cout << "\nProcedure cancelled" << std::endl;
                                    cancel = true;
                                    break;
                                }
                                if (checkDepositAndCollectCents(input_str, cents) == -1) {
                                    std::cout << "\nError: Invalid format, try again.";
                                } else {
                                    cont_dowhile = false;
                                }

                                    
                            } else if (input_chr.at(0) == 'n') {
                                cont_dowhile = false;
                            } else {
                                std::cerr << "Error: Unknown option" << std::endl;
                                cont_dowhile = true;
                            }
                        }
                    }
                    while(cont_dowhile);
                    
                    if (!cancel && atype.compare("basic") != 0) {
                        std::string helptext;
                        if (atype.compare("customer") == 0)
                            helptext = "\nEnter first name";
                        else if(atype.compare("enterprise") == 0)
                            helptext = "\nEnter business id";

                        if (collectToken(helptext, info1) == -1) {
                            std::cout << "\nProcedure cancelled" << std::endl;
                            cancel = true;
                            break;
                        }

                        if (atype.compare("customer") == 0)
                            helptext = "\nEnter last name";
                        else if (atype.compare("enterprise") == 0)
                            helptext = "\nEnter company name";
    
                        if (collectToken(helptext, info2) == -1) {
                            std::cout << "\nProcedure cancelled" << std::endl;
                            cancel = true;
                            break;
                        }
                        Pause();
                    }                            
                } 
            }
        
        } else { 
            cont_dowhile = true;
            std::cerr << "\nError: Invalid Account ID - IDs are five (5) chars long" << std::endl;
        }           
    }
    while(cont_dowhile && !cancel);

    return cancel;
}

void Banking::addAccount() {

    bool cont_dowhile = true; 
    std::string input_chr;

    do 
    {
        help_addAccount();
        std::getline(std::cin, input_chr);

        if (input_chr.empty() == 1) {
            std::cerr << "Error: No option given" << std::endl;
            cont_dowhile = true;
        } else if (input_chr.length() > 1) {
            std::cerr << "Error: Invalid option" << std::endl;
            cont_dowhile = true;
        } else {

            std::string account_id, info1, info2;
            std::string cents = "000";
            BasicAccount* account;
            
            switch (input_chr.at(0)) {
                case 'b': {
                    if (!collectAccountInfo("basic", account_id, cents, info1, info2)) {
                        account = new BasicAccount("basic", account_id, cents, time(0));
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        dbmanager->writeAccountToFile(account);
                        std::cout << "\n[ADDED NEW BASIC ACCOUNT]"; 
                        account->getAccountDetails();
                    }
                    Pause();
                    break;
                }
                case 'c': {
                    if(!collectAccountInfo(std::string("customer"), account_id, cents, info1, info2))                     {
                        account = new CustomerAccount("customer", account_id, 
                            cents, info1, info2, time(0));
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        dbmanager->writeAccountToFile(account);
                        std::cout << "\n[ADDED NEW CUSTOMER ACCOUNT]:";
                        account->getAccountDetails();
                    }
                    Pause();
                    break;
                }
                case 'e': {
                    if(!collectAccountInfo(std::string("enterprise"), account_id, cents, info1, info2)) {
                        account = new EnterpriseAccount("enterprise", account_id, 
                            cents, info1, info2, time(0));
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        dbmanager->writeAccountToFile(account);
                        std::cout << "\n[ADDED NEW ENTERPRISE ACCOUNT]";  
                        account->getAccountDetails(); 
                    }
                    Pause();
                    break;
                }
                case 'q':
                    cont_dowhile = false;
                    std::cout << "\nReturn to main menu" << std::endl;
                    break;
                default:
                    std::cout << "\nError: Unknown option" << std::endl;
                    break;
            }
        
        }
    }
    while(cont_dowhile);
    
}

int Banking::execute() {

    // Instantiates from the DBManager, and reads accounts from the accountIdDb
    dbmanager = new DBManager();
    dbmanager->readAccountInfoFromFile(accounts);

    bool cont_dowhile = true;
    std::string input_str;

    do 
    {   
        printheader();   
        listAccounts();
        help_collectDeposit();
        help();
        std::getline(std::cin, input_str);

        if (input_str.empty() == 1) {
            std::cerr << "Error: No option given" << std::endl;
            cont_dowhile = true; 
        } else if (input_str.length() > 1) {
            std::cerr << "Error: Invalid option" << std::endl;
            cont_dowhile = true;
        } else {
            std::string op;
            switch (input_str.at(0)) {
                case 'a':
                    addAccount();
                    break;
                case 'r':
                    op = "remove";
                    selectOperation(op, &Banking::remove);
                    Pause();
                    break;
               case 's':
                    op = "show";
                    selectOperation(op, &Banking::show);
                    Pause();
                    break;
                case 'd':
                    op = "decrease";
                    selectOperation(op, &Banking::decrease);
                    Pause();
                    break;
                case 'i':
                    op = "deposit";
                    selectOperation(op, &Banking::deposit);
                    Pause();
                    break;
                case 'q':
                    cont_dowhile = false;
                    break;
                default:
                    std::cout << "Error: Invalid option" << std::endl;
                    break;
            }
        }
    } 
    while(cont_dowhile);
       
    // Erase everything
    accountsMap_t::iterator it;

    for (it = accounts.begin(); it !=accounts.end(); ++it) {
        delete it->second;
        accounts.erase(it);
    }
 
    std::cout << "Program terminates...\n";

    return 0;

}
