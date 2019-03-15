#include "utils.h"
#include <iostream>
#include <limits>

void Pause() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n' );
}

bool containsOnlyDigits(std::string& digits) {

    int l = digits.length();
    bool flag = true;
    for (int i = 0; i < l; ++i) {
        int digit = static_cast<int>(digits.at(i));
        if ( digit < 48 || digit > 57 ) {
            flag = false;
            break;
        } 
    }

    return flag;
}

std::string collectEuros() {

    bool cont_dowhile = false;
    std::string euros;

    do
    {
        std::cout << "Euros: ";
        getline(std::cin, euros);
        if(!containsOnlyDigits(euros)) {
            cont_dowhile = true;
            std::cout << "Please, only digits (0,1,...9)!" << std::endl;
        } else {
            cont_dowhile = false;
        }
    }
    while(cont_dowhile);
 
    return euros;
}

std::string collectCents() {

    bool cont_dowhile = false;
    std::string cents;
    do
    {
        std::cout << "Cents: ";
        getline(std::cin, cents);
        if(!containsOnlyDigits(cents)) {
            cont_dowhile = true;
            std::cout << "Please, only digits (0,1,...9)!" << std::endl;
                                
        } else {
            if (cents.length() < 3) {
                cont_dowhile = false;
                
            } else {
                std::cout << "Max allowed is 99 cents!" << std::endl;
                cont_dowhile = true;
            }
        }
    }
    while(cont_dowhile);

    if (cents.length() == 1) {
        cents = "0" + cents;
    }
 
    return cents;

}


