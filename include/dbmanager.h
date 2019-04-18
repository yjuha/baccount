#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "types.h"
#include "basic_account.h"
#include "customer_account.h"
#include "enterprise_account.h"

namespace fs = boost::filesystem;

class DBManager {
    std::fstream accountId_f;
    std::string accountId_filename;
    bool accountsExist;
    std::vector<std::string> accountIdVec;
    std::vector<std::string> readAccountIdFileToVec();
    bool makeDbDir();
    bool writeAccountIdToFile(std::string accountId);
public:
    //! Default constructor
    DBManager() : accountId_filename("./accountsId"), 
                    accountsExist(makeDbDir()), 
                    accountIdVec(readAccountIdFileToVec()) {}

    std::vector<std::string> get_accountIdVec() { return accountIdVec; }

    //! Write account info to db
    bool writeAccountToFile(BasicAccount* account);    
    //! Read account info from db files
    void readAccountInfoFromFile(accountsMap_t& accounts);
    //! Remove account
    bool removeAccountFromFile(std::string aid);
};



#endif 
