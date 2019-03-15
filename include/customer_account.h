#ifndef CUSTOMER_ACCOUNT_H_
#define CUSTOMER_ACCOUNT_H_

#include "types.h"
#include "basic_account.h"

class CustomerAccount : public BasicAccount
{
    std::string firstname;
    std::string lastname;

public:
    CustomerAccount(string_t atype, string_t aid, string_t e, string_t c, string_t info1, string_t info2) : 
        firstname(info1), lastname(info2), BasicAccount(atype, aid, e, c) {} 
    virtual void getAccountDetails();

};

#endif
