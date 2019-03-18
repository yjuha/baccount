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
    std::string account_type;

public:
    BasicAccount(std::string atype, std::string aid, std::string c) : 
        balance(c), account_type(atype), objid(aid) {}
    virtual void getAccountDetails();
    void modifyBalance(std::string&);
    std::string get_cents() {return balance.cents;}
    void set_cents(std::string cents) {balance.cents=cents;}

};

#endif
