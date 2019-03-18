/*!
 *  @file banking.h
 *  @brief This header contains the banking manager class definition. This class
 *  is responsible for all management happening in the application, including
 *  account addition, modification, remove, etc.
 *
 *  @author Juha Ylioinas
 *
 *  @date 17/3/2019 
 *
 */
#ifndef BANKING_H_
#define BANKING_H_

#include <string>
#include <vector>
#include <map>

class BasicAccount; //forward declaration for BasicAccount class

typedef std::map<std::string, BasicAccount*> accountsMap_t;

class Banking {

    accountsMap_t accounts; /*!< a map with (key, val) =(std::string ACCOUNT_ID, BasicAccount* account) */
 
    //! A member print function for app title 
    void printheader() const;    
    //! Helper print function for main menu 
    void help() const;
    //! Helper print function for account addition
    void help_addAccount() const;
    //! Helper print function for deposit collection
    void help_collectDeposit() const;
    //! Helper print function for account id collection
    void help_collectAID() const;
    //! A function to collect the necessary information to construct an account instance.
     /*!
     *  \param A string reference to tick which kind of information to collect.
     *  \param A string reference to return the generated ACCOUNT_ID
     *  \param A string reference to return cents
     *  \param A string reference to return detailed information
     *  \param A string reference to return another piece of detailed information
     */
    //! A member to modify (increase/decrease) the balance in an account.
     /*!
     *  This method collects all necessary information for new account generation
     *  @param atype        Account type (basic, customer, or enterprise) std::string
     *  @param account_id   Account ID std::string
     *  @param cents        Initial deposit in cents
     *  @param info1        Additional information for customer and enterprise instances
     *  @param info2        Additional information for customer and enterprise instances
     */
    bool collectAccountInfo(std::string atype, std::string& account_id, std::string& cents, std::string& info1, std::string& info2);
    //! A member to add new account (basic, customer, or enterprise).
     /*!
     *  A method for adding new account
     */ 
    void addAccount(); 
    //! A member to modify account
    int modify(std::string&);
    //! A member to increase account deposit
    int increase(std::string&);
    //! A member to decrease account deposit
    int decrease(std::string&);
    //! A mamber to show account details
    int show(std::string&);
    //! A member to remove an account
    int remove(std::string&);
    //! A member to pick the operation (modify, increase, decrease, show, and remove) 
    void selectOperation(std::string&, int (Banking::*myop)(std::string&));
    //! A member to list all accounts by ID
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
