#ifndef CUSTOMER_ACCOUNT_H_
#define CUSTOMER_ACCOUNT_H_

#include "basic_account.h"

class CustomerAccount : public BasicAccount
{
public:
    CustomerAccount(std::string caname) : BasicAccount(caname) {} 

}

#endif
