cmake_minimum_required(VERSION 3.9.0)

# --------------- vpr-overwatch --------------- #

project(vpr-overwatch CXX)
set(TARGET vpr-overwatch)
set(EXE_NAME vpr-overwatch)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(${TARGET} ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_DIR include)
set(SOURCE_DIR src)

set(SOURCES
    # C sources
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/parser.cpp
    ${SOURCE_DIR}/util.cpp
    ${SOURCE_DIR}/watcher.cpp
    # C includes
    ${INCLUDE_DIR}/parser.hpp
    ${INCLUDE_DIR}/types.hpp
    ${INCLUDE_DIR}/util.hpp
    ${INCLUDE_DIR}/watcher.hpp
)

## Application executable and link dependencies
add_executable(${TARGET} ${SOURCES})

## Set architecture suffix
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${EXE_NAME}
)

# ------------- TESTING ------------- #

project(run-tests CXX)
set(TEST_TARGET run-tests)

include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/tests)

set(TEST_DIR tests)

set(TEST_SOURCES
    # CXX test sources
    ${TEST_DIR}/test.cpp
    ${TEST_DIR}/parser_test.cpp
    ${TEST_DIR}/util_test.cpp
    ${TEST_DIR}/watcher_test.cpp
    # CXX test includes
    ${TEST_DIR}/parser_test.hpp
    ${TEST_DIR}/watcher_test.hpp
    ${TEST_DIR}/util_test.hpp
    # CXX sources
    ${SOURCE_DIR}/parser.cpp
    ${SOURCE_DIR}/util.cpp
    ${SOURCE_DIR}/watcher.cpp
    # CXX includes
    ${INCLUDE_DIR}/parser.hpp
    ${INCLUDE_DIR}/types.hpp
    ${INCLUDE_DIR}/util.hpp
    ${INCLUDE_DIR}/watcher.hpp
)

add_executable(${TEST_TARGET} ${TEST_SOURCES}) 
