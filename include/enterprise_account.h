#ifndef ENTERPRISE_ACCOUNT_H_
#define ENTERPRISE_ACCOUNT_H_

#include "basic_account.h"

class EnterpriseAccount : public BasicAccount
{
    std::string business_id;
    std::string company_name;
        
public:
    EnterpriseAccount(std::string atype, std::string aid, std::string c, std::string info1, std::string info2) : 
        business_id(info1), company_name(info2), BasicAccount(atype, aid, c) {} 
    virtual void getAccountDetails();
};

#endif
