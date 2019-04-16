#include "dbmanager.h"

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

        while ( accountId_f ) {

            std::string accountId;
            std::getline(accountId_f, accountId);
            accountIdVec.push_back(accountId);

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
