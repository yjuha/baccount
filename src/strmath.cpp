#include "strmath.h"
#include <string>

void initArrayToZero(int* arr, int length) {
    for (int i = 0; i < length; ++i) {
        arr[i] = 0;
    }
}

void string2IntArr(int* arr, int length, std::string numstr) {
    int numstr_len = numstr.length();
    int j = numstr_len - 1;
    for (int i = length - 1; i >= length - numstr_len; --i, --j) {
        arr[i] = static_cast<int> (numstr.at(j)) - 48;
    }
}

std::string IntArr2string(int* arr, int length) {

    std::string result_arr = "";

    for (int i = 0; i < length; ++i) {
        result_arr += std::string(1, static_cast<char> (arr[i] + 48));
    }

    result_arr.erase(0, result_arr.find_first_not_of('0'));

    return result_arr;

}

bool strmath::compare(std::string& num1str, std::string& num2str) {

    if (num1str.compare(num2str) == 0) {
        return true;
    }

    int l1 = num1str.length();
    int l2 = num2str.length();

    bool valid;

    if ( l1 > l2 ) {

        valid = true;

    } else if ( l1 == l2 ) {

        for ( int j = l1 - 1; j >= 0; --j ) {
            if(num1str.at(j) > num2str.at(j))
                valid = true;
            else if(num1str.at(j) < num2str.at(j)) 
                valid = false;
        }

    } else {
       valid = false;
    }

    return valid;

}

std::string strmath::subtract(std::string num1str, std::string num2str) {
    int length = 100;

    int *num1 = new int[length];
    int *num2 = new int[length];
    int *result = new int[length];

    initArrayToZero(num1, length);
    initArrayToZero(num2, length);
    initArrayToZero(result, length);

    string2IntArr(num1, length, num1str);
    string2IntArr(num2, length, num2str);

    int i, j;
    int pointer = length - 1;
    int temp;

    for( i = length - 1; i >= 0; --i, --pointer ) {
        temp = num1[i] - num2[i];

        if(temp >= 0) {
            result[pointer] = temp;
        } else { 
            result[pointer] = temp + 10;
            num1[i-1] = num1[i-1]  - 1;
      }
    }
    
    std::string newbalance = IntArr2string(result, length);


    delete [] num1;
    delete [] num2;
    delete [] result;

    return newbalance;

}   

std::string strmath::add(std::string num1str, std::string num2str) {
    int length = 100;

    int *num1 = new int[length];
    int *num2 = new int[length];
    int *result = new int[length];

    initArrayToZero(num1, length);
    initArrayToZero(num2, length);
    initArrayToZero(result, length);

    string2IntArr(num1, length, num1str);
    string2IntArr(num2, length, num2str);

    int i, j;
    int pointer = length - 1;
    int temp;

    for(i = length - 1; i >= 0; --i, --pointer) {
        temp = num1[i] + num2[i] + result[pointer];

        if(temp < 10) {
            result[pointer] = temp;
        } else {
            result[pointer] = temp - 10;
            result[pointer-1] = 1;
        }
    }

    std::string newbalance = IntArr2string(result, length);


    delete [] num1;
    delete [] num2;
    delete [] result;

    return newbalance;

}

