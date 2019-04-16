#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "basic_account.h"

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
    DBManager() : accountId_filename("./accountsId"), accountsExist(makeDbDir()), accountIdVec(readAccountIdFileToVec()) {}
    std::vector<std::string> get_accountIdVec() { return accountIdVec; }

    //! Write account details to db
    bool writeAccountToFile(BasicAccount* account);    

};



#endif 
