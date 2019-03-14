#ifndef BASIC_ACCOUNT_H_
#define BASIC_ACCOUNT_H_

#include "types.h"
#include "account.h"
#include "balance.h"
#include <iostream>
#include <string>
#include <fstream>

class BasicAccount : public Account
{
protected:

    std::fstream file_account;

    Balance balance;
    std::string account_id;
    std::string account_type;

public:
    BasicAccount(string_t atype) : account_id("none"), balance("0","0"), account_type(atype) {}
    BasicAccount(string_t atype, string_t aid, string_t e, string_t c) : 
        account_id(aid), balance(e,c), account_type(atype) {}
    virtual void getAccountDetails() const;
    void display_account_id() const { std::cout << account_id << std::endl;}
    void display_balance() const {std::cout << balance.euros << " euros " \
        << balance.cents << " cents" << std::endl;}
    void display_account_type() const { std::cout << account_type << std::endl;}
    void set_balance(std::string&, std::string&);
    void modifyBalance(std::string&);

};

#endif
