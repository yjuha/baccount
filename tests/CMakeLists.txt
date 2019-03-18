if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

# (2) Our unit tests sources
set(TEST_APP ${APP}_tests)
set(TEST_SOURCES
    BalanceStructTest.cpp
    UtilsTest.cpp
    ../src/utils.cpp
    main.cpp
)

# (3) Take care of include directories
include_directories(${CPPUTEST_INCLUDE_DIRS} ../include/)
link_directories(${CPPUTEST_LIBRARIES})

# (4) Build the unit tests objects and link then with the app library
add_executable(${TEST_APP} ${TEST_SOURCES})
target_link_libraries(${TEST_APP} ${CPPUTEST_LDFLAGS})

# (5) Run the test once the build is done
add_custom_command(TARGET ${TEST_APP} COMMAND ./${TEST_APP} POST_BUILD)
