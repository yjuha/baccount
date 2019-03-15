cmake_minimum_required(VERSION 3.4)

set(APP baccount)

project(${APP})

add_executable(${APP} main.cpp banking.cpp objid.cpp enterprise_account.cpp customer_account.cpp basic_account.cpp utils.cpp)

target_include_directories(${APP} PRIVATE ${PROJECT_SOURCE_DIR}/include)
