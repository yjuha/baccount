/*!
 *  @file utils.h
 *  @brief this 
 *
 *
 */

#include "utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>

int checkDepositAndCollectCents(std::string& deposit, std::string& cents) {

    cents.clear();
    int retval = 0;
    
    /// deposit empty
    if (deposit.empty() == 1) { 
        retval = -1; 
    } 

    /// deposit contains only accepted chars 
    else if (deposit.find_first_not_of("0123456789,") != std::string::npos) {
        retval = -1;
    }

    /// deposit contains only one comma
    else if (deposit.length() == 1 && deposit.at(0) == ',') {
        retval = -1;
    }
    
    /// other cases
    else {
        // trim (erase leading and ending zeros)
        deposit = deposit.erase(0, deposit.find_first_not_of("0"));
        //deposit = deposit.erase(deposit.find_last_not_of("0") + 1);

        if (deposit.length() == 1 && deposit.at(0) == ',') {
            cents = "000";
        } else {
            
            /// split deposit into tokens based on commas and do further checks
            std::vector<std::string> tokens;
            std::string token;
            std::stringstream tokenStream(deposit);

            while (std::getline(tokenStream, token, ',')) {
                tokens.push_back(token);
            }
        
            int tlen = tokens.size();

            if ( tlen == 1 ) { // cases "xx" or "xx,"

                cents = tokens[0] + "00";
           
            } 
            
            else if ( tlen == 2 ) {
                
                if ( tokens[1].length() < 3 ) {

                    if ( tokens[0].empty() == 0 ) // case yy,xx
                        cents+=tokens[0];
                    else 
                        cents+="0";

                    if ( tokens[1].length() == 1 ) {
                        cents+=tokens[1] + "0";
                    }
                    else {
                    
                          cents+=tokens[1];
                    }
                } else {
                    retval = -1;
                } 
            } else {
                retval = -1;
            }
        }
    }
    

    return retval;
}



int collectToken(std::string& helptext, std::string& mytoken) {
    
    bool cont_dowhile = false;
    int retval;

    do
    {
        std::cout << helptext << " (press 'q' to cancel) > ";  
        std::string input;
        getline(std::cin, input);

        /// enter pressed
        if ( input.empty() == 1 ) {
            cont_dowhile = true;
        } 
        /// 'q' or some other
        else if (input.length() == 1) {
        
            if (input.at(0) == 'q') {

                retval = -1;
                cont_dowhile = false;
            } 
            
            else {

                mytoken = input; // token can be one character long ('q' is reserved)
                retval = 0;
                cont_dowhile = false;
            }
        } 
        /// other
        else {

            mytoken = input;
            retval = 0;
            cont_dowhile = false;
        }

 
    }while(cont_dowhile);
    return retval;
}

void Pause() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n' );
}
/*!
 * A help function to check that all chars in input string reference are digits
 *  returns true/false based on success
 */
bool containsOnlyDigits(std::string& instr) {

    bool accept = true;

    // if the current character is a digit, that's fine
    for ( unsigned int j = 0; j < instr.length() && accept; ++j )
    {
        if (isdigit(instr.at(j)))
            continue;

        accept = false;
    
    }
    
    return accept;

}

