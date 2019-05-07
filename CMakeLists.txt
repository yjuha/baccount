cmake_minimum_required(VERSION 3.4)

set(APP baccount)

project(${APP})

find_package(Boost 1.65 REQUIRED COMPONENTS
                filesystem)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
set(CMAKE_BUILD_TYPE Debug)

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
target_link_libraries(${APP} Boost::filesystem)

option(COMPILE_TESTS "Compile tests" OFF)
if(COMPILE_TESTS)
 add_subdirectory(tests)
endif(COMPILE_TESTS)
