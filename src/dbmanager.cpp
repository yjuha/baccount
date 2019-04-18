#include "dbmanager.h"
#include "utils.h"
#include <cstdio>
/*!
 *
 *
 */
bool DBManager::writeAccountIdToFile(std::string accountId) {

    accountId_f.open(accountId_filename, std::fstream::out | std::fstream::app);

    if ( !accountId_f.is_open() ) {
        std::cout << "Error: unable to open file" << std::endl;
        return false;
    } else {
        accountId_f << accountId << std::endl;
        return true;
    } 

}

std::vector<std::string> DBManager::readAccountIdFileToVec() {
    
    std::vector<std::string> accountIdVec;

    accountId_f.open(accountId_filename, std::fstream::in);

    if ( !accountId_f.good() ) {
    
        std::cout << "\nDatabase empty"
                     "\nNew accountsId database file created" << std::endl;

        accountId_f.open(accountId_filename, std::fstream::in | std::fstream::out | std::fstream::app);
    
    } else {

        std::cout << "\nReading existing account Ids." << std::endl;

        std::string line;
        while ( getline(accountId_f, line ) ) {
            accountIdVec.push_back(line);
        }
    }

    accountId_f.close();

    return accountIdVec;

}

bool DBManager::makeDbDir() {

    std::string p = "./accounts";
    fs::path accountsDirPath(p);

    if (exists(accountsDirPath)) {
        std::cout << "Folder exits" << std::endl;
        return true;
    } else {
        std::cout << "Created a folder for accounts" << std::endl;
        fs::create_directory(accountsDirPath);
        return false;
    }

}

bool DBManager::writeAccountToFile(BasicAccount* account) {

    if ( account->writeAccountDetailsToFile() ) {

        if ( writeAccountIdToFile(account->getAccountId()) ) {

            std::cout << "Account written to DB" << std::endl;

            return true;

        } else {

            return false;

        }

    } else {

        return false;

    }

}

void DBManager::readAccountInfoFromFile( accountsMap_t& accounts ) {

    std::vector<std::string>::const_iterator it;
    it = accountIdVec.begin();

    std::cout << "Reading accounts:\n";

    if ( accountIdVec.begin() == accountIdVec.end() ) {

        std::cout << "### EMPTY ###" << std::endl;

    } else {

        // loop through all accounts in accountIDs file
        while ( it != accountIdVec.end() ) {
            std::string accountID = *it;

            // std::cout << accountID << "\n";
            
            std::string p = "./accounts";
            std::string account_fp = p + "/" + accountID;

            std::fstream account_f;
            account_f.open(account_fp, std::fstream::in);

            if ( !account_f.is_open() ) {
                std::cout << "Error: unable to open account with ID: " << accountID << std::endl;
            } else {

                std::string line;
                std::vector<std::string> account_info;
                while ( getline(account_f, line) ) {
                    
                    account_info.push_back(line);    
                }
                
                std::string id;
                std::string atype;
                std::string cents;
                std::string info1;
                std::string info2;
                std::string timecreated;

                id = account_info[0];
                atype = account_info[1];
                cents = account_info[2];

                if (cents.compare("0") == 0)
                    cents = "000"; //this is for printing

                if ( account_info.size() > 4 ) {

                    info1 = account_info[3];
                    info2 = account_info[4];
                    timecreated = account_info[5];

                } else {

                    timecreated = account_info[3];

                }
                    
                time_t timecreated_t = convertTimeString2time_t(timecreated);

                // Add new account here
                BasicAccount* account;

                if ( atype.compare("basic") == 0 ) {
                    std::cout << "Added basic" << std::endl; 
                    account = new BasicAccount("basic", id, cents, timecreated_t);
                    accounts.insert(std::pair<std::string, BasicAccount*>(id, account));

                } else if ( atype.compare("customer") == 0 ) {
                    std::cout << "Added customer" << std::endl;
                    account = new CustomerAccount("customer", id, cents, info1, info2, timecreated_t);
                    accounts.insert(std::pair<std::string, BasicAccount*>(id, account));
                    std::cout << "jep" << std::endl;

                } else if ( atype.compare("enterprise") == 0 ) {
                    std::cout << "Added enterprise" << std::endl;
                    account = new EnterpriseAccount("enterprise", id, cents, info1, info2, timecreated_t);
                    accounts.insert(std::pair<std::string, BasicAccount*>(id, account));

                }



            }
            ++it;
        }
    }
}

bool DBManager::removeAccountFromFile ( std::string aid ) {

    accountId_f.open ( accountId_filename, std::fstream::in );

    if ( !accountId_f.is_open() ) {

        std::cout << "Error: unable to open file" << std::endl;
        return false;

    } else {
        
        std::ofstream accountId_temp_f;
        accountId_temp_f.open("accountsId_temp", std::fstream::out | std::fstream::app );

        std::string line;
        while ( getline(accountId_f, line) ) {
            if (line != aid)
                accountId_temp_f << line << std::endl;
        
        }
        
        accountId_temp_f.close();
        accountId_f.close();

        remove("accountsId");
        rename("accountsId_temp", "accountsId");
        
        std::string aid_filepath("./accounts/"); 
        aid_filepath = aid_filepath + aid;

        remove(aid_filepath.c_str());
    } 

    return true;
}
