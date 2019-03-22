cmake_minimum_required(VERSION 3.4)

set(APP baccount)

project(${APP})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

add_executable(${APP} src/main.cpp 
                      src/banking.cpp 
                      src/objid.cpp 
                      src/enterprise_account.cpp 
                      src/customer_account.cpp 
                      src/basic_account.cpp 
                      src/utils.cpp
                      src/strmath.cpp
                      src/dbmanager.cpp)

target_include_directories(${APP} PRIVATE ${PROJECT_SOURCE_DIR}/include)

option(COMPILE_TESTS "Compile tests" OFF)
if(COMPILE_TESTS)
 add_subdirectory(tests)
endif(COMPILE_TESTS)
