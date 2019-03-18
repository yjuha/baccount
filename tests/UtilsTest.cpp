// t/test.cpp
#include "CppUTest/TestHarness.h"
#include "utils.h"
 
TEST_GROUP(TestGroup2)
{
};
 
TEST(TestGroup2, FirstExample)
{
    std::string deposit1 = ",0";
    std::string deposit2 = ",";
    std::string deposit3 = "0,";
    std::string deposit4 = "0,0";
    std::string deposit5 = "000000000000000,00";
    std::string deposit6 = "1234,5";

    std::string cents;

    int retval = checkDepositAndCollectCents(deposit1, cents);
    STRCMP_EQUAL("000", cents.c_str())
    LONGS_EQUAL(0, retval)

    retval = checkDepositAndCollectCents(deposit2, cents);
    LONGS_EQUAL(-1, retval)

    retval = checkDepositAndCollectCents(deposit3, cents);
    STRCMP_EQUAL("000", cents.c_str())
    LONGS_EQUAL(0, retval)

    retval = checkDepositAndCollectCents(deposit4, cents);
    STRCMP_EQUAL("000", cents.c_str())
    LONGS_EQUAL(0, retval)

    retval = checkDepositAndCollectCents(deposit5, cents);
    STRCMP_EQUAL("000", cents.c_str())
    LONGS_EQUAL(0, retval)

    retval = checkDepositAndCollectCents(deposit6, cents);
    STRCMP_EQUAL("123450", cents.c_str())
    LONGS_EQUAL(0, retval)


}
