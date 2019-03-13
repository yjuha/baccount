#ifndef BASIC_ACCOUNT_H_
#define BASIC_ACCOUNT_H_

#include "account.h"
#include <string>
#include <fstream>

class BasicAccount : public Account
{
protected:
    std::string account_name;
    std::ofstream ofile;
    std::ifstream ifile;
public:
    BasicAccount() : account_name("none") {}
    BasicAccount(std::string aname) : account_name(aname) {} 
    virtual std::string getAccountDetails() const;
}

#endif
