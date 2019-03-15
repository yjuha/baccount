#ifndef BASIC_ACCOUNT_H_
#define BASIC_ACCOUNT_H_

#include "account.h"
#include "objid.h"
#include "balance.h"

#include <iostream>
#include <string>
#include <fstream>

class BasicAccount : public Account
{
protected:

    Balance balance;
    ObjId objid;
    std::string account_id;
    std::string account_type;

public:
    BasicAccount(std::string atype) : account_id("none"), balance("0","0"), account_type(atype) {}
    BasicAccount(std::string atype, std::string aid, std::string e, std::string c) : 
        account_id(aid), balance(e,c), account_type(atype), objid(aid) {}
    virtual void getAccountDetails() ;
    void set_balance(std::string&, std::string&);
    void modifyBalance(std::string&);

};

#endif
