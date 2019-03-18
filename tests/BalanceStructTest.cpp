// t/test.cpp
#include "CppUTest/TestHarness.h"
#include "balance.h"
 
TEST_GROUP(TestGroup1)
{
};
 
TEST(TestGroup1, FirstExample)
{
  std::string a = "0";
  Balance balance(a);
  const char* myreturn = balance.get_cents().c_str();
 
  STRCMP_EQUAL("0", myreturn)
}
