/*!
 *
 *      @file customer_account.h
 *      @brief This header is for the customer account class which 
 *      is derived from the basic account class. It contains an implementation of
 *      the pure virtual method "getAccountDetails()" defined in the account class definition (account.h)
 *
 *      @author Juha Ylioinas
 *
 *      @date 17/3/2019
 */

#ifndef CUSTOMER_ACCOUNT_H_
#define CUSTOMER_ACCOUNT_H_

#include "basic_account.h"

class CustomerAccount : public BasicAccount
{
    std::string firstname; /*!< member firstname of the customer */
    std::string lastname; /* !< member lastname of the customer*/

public:
    //! A constructor
    CustomerAccount(std::string atype, std::string aid, std::string c, std::string info1, std::string info2) : 
        firstname(info1), lastname(info2), BasicAccount(atype, aid, c) {}
    /*!
     * a member to print the details of an account
     *
     */
    virtual void getAccountDetails();

};

#endif
