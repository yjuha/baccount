/*!
 *      @file account.h
 *      @brief This is an abstract base class for different account types.
 *      It contains one pure virtual method which must be
 *      re-defined in any derived class.
 *
 *      @author Juha Ylioinas
 *
 *      @date 17/3/2019
 *
 */
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>

class Account {
public:
    /*!
     *  This is a pure virtual method to print account details.
     *  @author Juha Ylioinas
     *  @date 17/3/2019
     */
    virtual void getAccountDetails() = 0;

};

#endif
