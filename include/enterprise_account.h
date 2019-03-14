#ifndef ENTERPRISE_ACCOUNT_H_
#define ENTERPRISE_ACCOUNT_H_

#include "types.h"
#include "basic_account.h"

class EnterpriseAccount : public BasicAccount
{
    std::string business_id;
    std::string company_name;
        
public:
    EnterpriseAccount(string_t atype, string_t aid, string_t e, string_t c, string_t info1, string_t info2) : 
        business_id(info1), company_name(info2), BasicAccount(atype, aid, e, c) {} 
    virtual void getAccountDetails() const;
};

#endif
