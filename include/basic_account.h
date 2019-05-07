#ifndef BASIC_ACCOUNT_H_
#define BASIC_ACCOUNT_H_

#include "account.h"
#include "objid.h"
#include "balance.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

class BasicAccount : public Account
{
protected:

    Balance balance;
    ObjId objid;
    std::string account_type;

public:
    BasicAccount(std::string atype, std::string aid, std::string c, time_t mytime) : 
        balance(c), account_type(atype), objid(aid, mytime) {}
    virtual void getAccountDetails();
    virtual std::string getAccountId();
    virtual bool writeAccountDetailsToFile();
    virtual void set_timemodified() { objid.set_timemodified(); }
    void modifyBalance(std::string&);
    std::string get_cents() {return balance.cents;}
    void set_cents(std::string cents) {balance.cents=cents;}

};

#endif
