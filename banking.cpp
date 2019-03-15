#include "banking.h"
#include <iostream>
#include <sstream>

#include "utils.h"
#include "customer_account.h"
#include "enterprise_account.h"

void Banking::help() const {
    std::cout << "\n[MAIN MENU]" 
                    "\nOptions:" 
                    "\na - add an account"
                    "\nr - remove an account"
                    "\nm - modify an account"
                    "\nd - display account details" 
                    "\nl - list all accounts"
                    "\nq - quit program\n";
    
    std::cout << "\nEnter your option (a/r/m/d/l/q) > ";
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
void Banking::help_modifybalance(std::string& input) const {
     std::cout << "\n[MODIFY BALANCE of account ID" << input;
                    "\nOptions:"; 
                    "\nd - decrease balance"
                    "\ni - increase balance"
                    "\nq - cancel\n";
    
    std::cout << "\nEnter your option (d/i/q) > ";
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

int Banking::modify(std::string& input_str) {
    
    accountsMap_t::iterator it = accounts.find(input_str);
    if (it != accounts.end()) { 
        std::cout << "\n[ACCOUNT ID: " << it->first << "]";
        (it->second)->getAccountDetails();
        bool cont_dowhile = false;
        do 
        {
            help_modifybalance(input_str);
            std::string input_chr;
            std::getline(std::cin, input_chr);

            if (input_chr.empty() == 1) {
                cont_dowhile = true;
            } else if (input_chr.length() > 1) {
                std::cout << "Unknown option." << std::endl;
                cont_dowhile = true;
            } else {
                switch (input_chr.at(0)) {
                    case 'd':
                    case 'i':    
                        {
                        (it->second)->modifyBalance(input_chr);
                        (it->second)->getAccountDetails();
                        cont_dowhile = false;
                        break;
                        }
                    case 'q':
                        cont_dowhile = false;
                        return -2;
                        break;
                    default:
                        std::cout << "Unknown option." << std::endl;
                        cont_dowhile = true;                
                        break;    
                }
            }
        }
        while(cont_dowhile);
        return 0;
    } else {
        return -1;
    }
}

int Banking::display(std::string& input_str) {
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
        std::cout << "\n[ACCOUNT ID: " << it->first << "] removed\n";
        return 0;
    } else {
        return -1;
    }
} 

void Banking::selectOp(std::string& operation) {
    bool cont_dowhile = false;

    if(listAccounts()) {
        do
        {
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
                    
                    if ( operation.compare("display") == 0 ) {

                        if ( display(input_str) == -1 ) {
                            std::cerr << "\nError: Account ID " << input_str << " not found."; 
                            cont_dowhile = true;    
                        } else cont_dowhile = false;
                        Pause();  
                    } else if (operation.compare("remove") == 0) {

                         if ( remove(input_str) == -1 ) {
                            std::cerr << "\nError: Account ID " << input_str << " not found."; 
                            cont_dowhile = true;    
                        } else cont_dowhile = false;
                        Pause();
                    } else if (operation.compare("modify") == 0) {
                        int retval = modify(input_str);

                        if (retval == -1) {
                            std::cerr << "\nError: Account ID " << input_str << " not found."; 
                            cont_dowhile = true;    
                        } else if (retval == -2) {
                            std::cout << "\nProcedure cancelled";
                            cont_dowhile = false;
                        } else cont_dowhile = false;
                        Pause();

                    } else {
                        std::cout << "operation not implemented" << std::endl;
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

bool Banking::collectAccountDetails(std::string atype, std::string &account_id, \
        std::string &euros, std::string &cents, std::string &info1, std::string &info2) {

    bool cont_dowhile = false;
    bool cancel = false;
    do
    {   
        std::cout << "\n[NEW ACCOUNT] (press 'q' to cancel)";
        std::cout << "\nType in account ID > ";
        std::string input_str;
        std::getline(std::cin, input_str);
       
        if ( input_str.empty() == 1 ) {
            cont_dowhile = true; 
        } else if (input_str.length() == 1 ) {
            if (input_str.at(0) == 'q') {
                cont_dowhile = false;
                cancel = true;
            } else {
                cont_dowhile = true;
                std::cerr << "\nError: Invalid Account ID" 
                    " - IDs can contain 5 chars and all of them must be numbers" << std::endl;
            }
        } else if (input_str.length() == 5 ) {
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
                        std::string input_chr;
                        std::cout << "\nMake an initial deposit? (press 'q' to cancel)";
                        std::cout << "\nEnter your option (y/n) > ";
                        getline(std::cin, input_chr);

                        if ( input_chr.empty() == 1 ) {
                            cont_dowhile = true;
                        } else if (input_chr.length() > 1 ) {
                            std::cerr << "Error: Unknown option" << std::endl;
                            cont_dowhile = true;
                        } else {
                            if (input_chr.at(0) == 'y') {
                                euros = collectEuros();
                                cents = collectCents();
                            } else if (input_chr.at(0) == 'n') {
                                cont_dowhile = false;
                            } else if (input_chr.at(0) == 'q') {
                                cont_dowhile = false;
                                cancel = true;
                            } else {
                                std::cerr << "Error: Unknown option" << std::endl;
                                cont_dowhile = true;
                            }
                        }
                        

                    }
                    while(cont_dowhile);
                    
                    if (!cancel) {
                        std::string infotype1, infotype2;
                        if (atype.compare("basic") != 0) {
                            if (atype.compare("customer") == 0) {
                                infotype1 = "first name"; infotype2 = "last name";
                            } else if (atype.compare("enterprise") == 0) {
                                infotype1 = "business ID"; infotype2 = "company name";
                            }
                            std::cout << "Enter " << infotype1 << ": " << std::endl;
                            std::getline(std::cin, info1);
                            std::cout << "Enter " << infotype2 << ": " << std::endl;
                            std::getline(std::cin, info2);
                        }
                    }
                } 
            }
        
        } else { 
            cont_dowhile = true;
            std::cerr << "\nError: Invalid Account ID - IDs are five (5) chars long" << std::endl;
        }           
    }
    while(cont_dowhile);

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
            std::string euros = "0";
            std::string cents = "0";
            BasicAccount* account;
            
            switch (input_chr.at(0)) {
                case 'b': {
                    if (!collectAccountDetails("basic", account_id, euros, cents, info1, info2)) {
                        account = new BasicAccount("basic", account_id, euros, cents);
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        std::cout << "\n[ADDED NEW ACCOUNT]"; 
                        account->getAccountDetails();
                    } else {std::cout << "\nProcedure cancelled" << std::endl;}
                    Pause();
                    break;
                }
                case 'c': {
                    if(!collectAccountDetails(std::string("customer"), account_id, euros, cents, info1, info2))                     {
                        account = new CustomerAccount("customer", account_id, 
                            euros, cents, info1, info2);
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        std::cout << "\n[ADDED NEW ACCOUNT]:";
                        account->getAccountDetails();
                    } else {std::cout << "\nProceduce cancelled" << std::endl;}
                    Pause();
                    break;
                }
                case 'e': {
                    if(!collectAccountDetails(std::string("enterprise"), account_id, euros, cents, info1, info2)) {
                        account = new EnterpriseAccount("enterprise", account_id, 
                            euros, cents, info1, info2);
                        accounts.insert(std::pair<std::string, BasicAccount*>(account_id, account));
                        std::cout << "\n[ADDED NEW ACCOUNT]";  
                        account->getAccountDetails(); 
                    } else {std::cout << "\nProcedure cancelled" << std::endl;}
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

    bool cont_dowhile = true;
    std::string input_str;

    do 
    {   
        listAccounts();
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
                    selectOp(op);
                    break;
                case 'l':
                    listAccounts();
                    Pause();
                    break;
                case 'd':
                    op = "display";
                    selectOp(op);
                    break;
                case 'm':
                    op = "modify";
                    selectOp(op);
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
/*    for (std::vector<BasicAccount*>::iterator it = allAccounts.begin();
            it != allAccounts.end(); ) {
        delete *it;
        it = allAccounts.erase(it);
   
    }*/
 
    std::cout << "Program terminates...\n";

    return 0;

}
