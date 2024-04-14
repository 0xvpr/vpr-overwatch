## Application executable and link dependencies
add_executable(
    ${PROJECT_NAME}
    main.cpp
    parser.cpp
    util.cpp
    watcher.cpp
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Ofast>
            $<$<CXX_COMPILER_ID:GNU>:-fPIE>
            $<$<CXX_COMPILER_ID:GNU>:-funroll-loops>
            $<$<CXX_COMPILER_ID:GNU>:-Wall>
            $<$<CXX_COMPILER_ID:GNU>:-Wextra>
            $<$<CXX_COMPILER_ID:GNU>:-Werror>
            $<$<CXX_COMPILER_ID:GNU>:-Wshadow>
            $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
            $<$<CXX_COMPILER_ID:GNU>:-Wconversion>
)

#project(run-tests CXX)
#set(PROJECT_NAME run-tests)

#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/src)
#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/tests)

#set(TEST_DIR tests)

#set(TEST_SOURCES
    ## CXX test sources
    #${TEST_DIR}/test.cpp
    #${TEST_DIR}/parser_test.cpp
    #${TEST_DIR}/util_test.cpp
    #${TEST_DIR}/watcher_test.cpp
    ## CXX test includes
    #${TEST_DIR}/parser_test.hpp
    #${TEST_DIR}/watcher_test.hpp
    #${TEST_DIR}/util_test.hpp
    ## CXX sources
    #${SOURCE_DIR}/parser.cpp
    #${SOURCE_DIR}/util.cpp
    #${SOURCE_DIR}/watcher.cpp
    ## CXX includes
    #${INCLUDE_DIR}/parser.hpp
    #${INCLUDE_DIR}/types.hpp
    #${INCLUDE_DIR}/util.hpp
    #${INCLUDE_DIR}/watcher.hpp
#)

#add_executable(${PROJECT_NAME} ${TEST_SOURCES}) 
