#ifndef BANKING_H_
#define BANKING_H_

#include "types.h"
#include <string>
#include <vector>
#include <map>

#include "basic_account.h"

typedef std::map<std::string, BasicAccount*> accountsMap_t;

class Banking {

    accountsMap_t accounts; /*!< a map with (key, val) =(std::string ACCOUNT_ID, BasicAccount* account) */
    
    //! Helper print function for main menu 
    void help() const;
    //!Helper print function for addAccount
    void help_addAccount() const;
    //! A function to collect the necessary information to construct an account instance.
     /*!
     *  \param A string reference to tick which kind of information to collect.
     *  \param A string reference to return the generated ACCOUNT_ID
     *  \param A string reference to return euros 
     *  \param A string reference to return cents
     *  \param A string reference to return detailed information
     *  \param A string reference to return another piece of detailed information
     */
    bool collectAccountDetails(string_t, string_t&, string_t&, string_t&, string_t&, string_t&);
    //! A member to modify (increase/decrease) the balance in an account.
     /*!
     *  ...
     */
    void modifyAccount();
    //! A member to add new account (basic, customer, or enterprise).
     /*!
     *  ...
     */ 
    void addAccount();
    //! A member to remove an account in the database.
     /*!
     *  ...
     */ 
    void removeAccount();
    //! A member to remove an account in the database.
     /*!
     *  ...
     */ 
    void displayAccount(); 
    //! A member to diplay the details of an account
     /*!
     *  ...
     */ 
    bool listAccounts();
public:
    //! Default constructor
    Banking() {}
    //! A method to start the banking manager.
    /*!
     * \return An integer to represent succesful/faulty execution.
     */
    int execute();

};
#endif
