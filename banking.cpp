#include "banking.h"
#include <iostream>
#include <sstream>

#include "utils.h"
#include "customer_account.h"
#include "enterprise_account.h"


void Banking::help() const {
    std::cout << "\nOptions:" 
                    "\na - add an account"
                    "\nr - remove an account"
                    "\nm - modify an account"
                    "\nd - display account details" 
                    "\nl - list all accounts"
                    "\nq - quit program" << std::endl;
    
    std::cout << "Enter your option (a/r/m/d/l/q): " << std::endl;
}

void Banking::help_addAccount() const {
    std::cout << "\nAdd basic (press 'b'), customer ('c'),"
        " or enterprise ('e') account (cancel by pressing 'q')." << std::endl;
}

bool Banking::listAccounts() {

    std::cout << "\nAvailable accounts:" << std::endl;
    std::map<std::string, BasicAccount*>::iterator it;

    if( allAccountsMap.size() == 0) {
        std::cout << "DATABASE EMPTY" << std::endl;
        return false;
    } else {
        for (it = allAccountsMap.begin(); it !=allAccountsMap.end(); ++it) {
            std::cout << it->first << std::endl;
        }
        std::cout << "\n";
        return true;
    }

}

void Banking::modifyAccount() {
    
    if (listAccounts()) {
        bool cont_dowhile = false;

        //collect account id to modify, check if exists
        do
        {
            std::cout << "Enter account to be modified\n Account ID (press 'q' to cancel): " << "\n";
            std::string input_str;
            std::getline(std::cin, input_str);

            if (input_str.length() == 1 ) {
                if (input_str.at(0) == 'q') {
                    cont_dowhile = false;
                } else {
                    cont_dowhile = true;
                    std::cout << "The given account ID does not contain five (5) digits." 
                       "\nTry again (press 'q' to cancel)"  << std::endl;
                }   
            } else if ( input_str.length() == 5 ) {
                if ( !containsOnlyDigits(input_str)) {
                    cont_dowhile = true;
                    std::cout << "Please, only digits allowed!!!!" << std::endl;
                } else {
                    std::map<std::string, BasicAccount*>::iterator it = allAccountsMap.find(input_str);
                    if (it != allAccountsMap.end()) 
                    {
                        std::cout << "READY TO MODIFY ACCOUNT " << input_str << std::endl;
                        (it->second)->getAccountDetails();
                        bool cont_dowhile_2 = false;
                        do {
                            std::cout << "Decrease (press 'd') or increase ('i') balance" << std::endl;
                            std::string input_chr;
                            std::getline(std::cin, input_chr);

                            if (input_chr.length() > 1) {
                                std::cout << "Unknown option." << std::endl;
                                cont_dowhile_2 = true;
                            } else {
                                switch (input_chr.at(0)) {
                                    case 'd':
                                    case 'i':    
                                        {
                                        (it->second)->modifyBalance(input_chr);
                                        (it->second)->getAccountDetails();
                                        cont_dowhile_2 = false;
                                        break;
                                        }
                                    case 'q':
                                        cont_dowhile_2 = false;
                                        break;
                                    default:
                                        std::cout << "Unknown option." << std::endl;
                                        break;    
                                }
                            }
                        }
                        while(cont_dowhile_2);



                    } else {
                        std::cout << "Account ID " << input_str << " not found, sorry." 
                            "\nTry again (press 'q' to cancel)." << std::endl;
                        cont_dowhile = true;
                    }
                }
            } else {
                cont_dowhile = true;
                std::cout << "The given account ID does not contain five (5) digits."
                   "\nTry again (press 'q' to cancel)" << std::endl;
            }
        }
        while(cont_dowhile);
    } // if( listAccounts )
}

void Banking::removeAccount() {
    bool cont_dowhile = false;

    //collect account id to remove, check if exists
    do
    {
        std::cout << "Enter account to be removed\n Account ID: " << "\n";
        std::string input_str;
        std::getline(std::cin, input_str);

        if (input_str.length() == 1 ) {
            if (input_str.at(0) == 'q') {
                cont_dowhile = false;
            } else {
                cont_dowhile = true;
                std::cout << "The given account ID does not contain five (5) digits." 
                   "\nTry again (press 'q' to cancel)"  << std::endl;
            }   
        } else if ( input_str.length() == 5 ) {
            if ( !containsOnlyDigits(input_str)) {
                cont_dowhile = true;
                std::cout << "Please, only digits allowed!!!!" << std::endl;
            } else {
                std::map<std::string, BasicAccount*>::iterator it = allAccountsMap.find(input_str);
                if (it != allAccountsMap.end()) 
                {
                    cont_dowhile = false;

                    delete it->second;
                    allAccountsMap.erase(it);

                    std::cout << "Account (ID) " << it->first << " removed." << std::endl;

                } else {
                    std::cout << "Account ID " << input_str << " not found, sorry." 
                        "\nTry again (press 'q' to cancel)." << std::endl;
                    cont_dowhile = true;
                }
            }
        } else {
            cont_dowhile = true;
            std::cout << "The given account ID does not contain five (5) digits."
               "\nTry again (press 'q' to cancel)" << std::endl;
        }
    }
    while(cont_dowhile);

}

void Banking::collectBasicAccountDetails(int accountType, std::string &account_id, std::string &euros, std::string &cents, std::string &info1, std::string &info2) {

    bool cont_dowhile = false;

    //collect account id and check if reserved
    do
    {
        std::cout << "Enter account ID: " << "\n";
        std::string input_str;
        std::getline(std::cin, input_str);
       
        if ( containsOnlyDigits(input_str) ) {
            if ( input_str.length() == 5 ) {
                std::map<std::string, BasicAccount*>::iterator it = allAccountsMap.find(input_str);
                if (it != allAccountsMap.end()) {
                    cont_dowhile = true;
                    std::cout << "Account ID reserved, try new ID. " << std::endl;
                } else {
                    cont_dowhile = false;
                    account_id = input_str;
                }
            } else {
                cont_dowhile = true;
                std::cout << "Account ID's length must equal to five (5)" << std::endl;
            }

        } else {
            cont_dowhile = true;
            std::cout << "Account ID must contain only digits (0,1,...,9)" << std::endl;
        }

    }
    while(cont_dowhile);

    //collect initial deposit if given
    do
    {
        std::string input_chr;
        std::cout << "Make an initial deposit? (y/n)" << std::endl;
        getline(std::cin, input_chr);

        if(input_chr.length() > 1) {
            std::cout << "Error: Unknown option." << std::endl;
            cont_dowhile = true;
        } else {
            
            switch(input_chr.at(0)) {
                case 'y':
                    {
                        euros = collectEuros();    
                        cents = collectCents();

                        std::cout << "Deposit (" << euros << " euros " \
                            << cents << " cents) saved." << std::endl;
                    break;
                    }
                case 'n':
                    cont_dowhile = false;
                    break;
                default:
                    std::cout << "Error: Unkown option." << "\n";
                    cont_dowhile = true;
            }
            
        }

    }
    while(cont_dowhile);

    std::string infotype1, infotype2;

    if (accountType > 0) {

        if (accountType == 1) {
            infotype1 = "first name"; infotype2 = "last name";
        } else if (accountType == 2) {
            infotype1 = "business ID"; infotype2 = "company name";
        }

        std::cout << "Enter " << infotype1 << ": " << std::endl;
        std::getline(std::cin, info1);

        std::cout << "Enter " << infotype2 << ": " << std::endl;
        std::getline(std::cin, info2);

    }
}

void Banking::addAccount() {
 
    std::string input_chr;

    do 
    {
        help_addAccount();
        std::cout << "Enter your option (b/c/e/q): " << std::endl;
        std::getline(std::cin, input_chr);

        std::string account_id, euros, cents, info1, info2;

        if (input_chr.length() > 1) {
            help_addAccount();
        } else {

            switch (input_chr.at(0)) {
                case 'b': 
                    {
                    std::cout << "Adding basic account..." << std::endl; 
                    collectBasicAccountDetails(0, account_id, euros, cents, info1, info2);

                    BasicAccount* baccount = new BasicAccount("basic", account_id, euros, cents);
                    baccount->getAccountDetails();                    
                    allAccountsMap.insert(std::pair<std::string, BasicAccount*>(account_id, baccount));
                    return;
                    }
                case 'c':
                    {
                    std::cout << "Adding customer account..." << std::endl;
                    collectBasicAccountDetails(1, account_id, euros, cents, info1, info2);

                    CustomerAccount* caccount = new CustomerAccount("customer", account_id, 
                            euros, cents, info1, info2);
                    caccount->getAccountDetails();                    
                    allAccountsMap.insert(std::pair<std::string, BasicAccount*>(account_id, caccount));
                    return;
                    }
                case 'e':
                    {
                    std::cout << "Adding enterpise account..." << std::endl;
                    collectBasicAccountDetails(2, account_id, euros, cents, info1, info2);

                    EnterpriseAccount* eaccount = new EnterpriseAccount("enterprise", account_id, 
                            euros, cents, info1, info2);
                    eaccount->getAccountDetails();                    
                    allAccountsMap.insert(std::pair<std::string, BasicAccount*>(account_id, eaccount));
 
                    return;
                    }
                case 'q':
                    std::cout << "Canceling account addition..." << std::endl;
                    break;
                default:
                    std::cout << "Error: Unknown option" << std::endl;
                    break;
            }
        
        }
    }
    while(input_chr.at(0)!='q');
    
}

int Banking::execute() {

    bool cont_dowhile = true;
    std::string input_str;

    do 
    {
        help();
        std::getline(std::cin, input_str);

        if (input_str.length() > 1) {
            help();
        } else {
            switch (input_str.at(0)) {
                case 'a':
                    addAccount();
                    break;
                case 'r':
                    removeAccount();
                    break;
                case 'l':
                    listAccounts();
                    break;
                case 'm':
                    modifyAccount();
                    break;
                case 'q':
                    cont_dowhile = false;
                    break;
                default:
                    std::cout << "Error: Unknown option" << std::endl;
                    break;
            }
        }
    } 
    while(cont_dowhile);
       
    // Erase everything
    for (std::vector<BasicAccount*>::iterator it = allAccounts.begin();
            it != allAccounts.end(); ) {
        delete *it;
        it = allAccounts.erase(it);
   
    }
 
    std::cout << "Program terminates...\n";

    return 0;

}
