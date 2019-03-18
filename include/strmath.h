#ifndef STRMATH_H_
#define STRMATH_H_

#include <string>

void initArrayToZero(int* arr, int length);
void string2IntArr(int* arr, int length, std::string numstr);
std::string IntArr2string(int* arr, int length);
namespace strmath {

bool compare(std::string& num1str, std::string& num2str);

std::string subtract(std::string num1str, std::string num2str);
std::string add(std::string num1str, std::string num2str);
}
#endif

