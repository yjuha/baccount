#ifndef BANKING_H_
#define BANKING_H_

#include "types.h"
#include <string>
#include <vector>
#include <map>

#include "basic_account.h"

class Banking {

    std::string input_str;
    std::vector<BasicAccount*> allAccounts;
    std::map<std::string, BasicAccount*> allAccountsMap;
    void help() const;
    void help_addAccount() const;

    void collectBasicAccountDetails(int, string_t&, string_t&, string_t&, string_t&, string_t&);
    void modifyAccount();
    void addAccount();
    void removeAccount();
    bool listAccounts();
public:

    Banking() {}
    int execute();

};
#endif
