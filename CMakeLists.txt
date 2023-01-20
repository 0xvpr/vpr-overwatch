cmake_minimum_required(VERSION 3.9.0)

# --------------- vpr-overwatch --------------- #

project(vpr-overwatch C)
set(TARGET vpr-overwatch)
set(EXE_NAME vpr-overwatch)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(${TARGET} ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_DIR include)

set(SOURCE_DIR src)

set(SOURCES
    # C sources
    ${SOURCE_DIR}/main.c
    # C includes
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

#if (${ARCH} STREQUAL "x64")
	#project(run-tests C)
	#set(TESTS run-tests)

	#include_directories(${TESTS} /usr/local/share/mingw64/include)
	#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/include)
	#include_directories(${TESTS} ${CMAKE_CURRENT_BINARY_DIR}src/tests)

	#set(TESTS_DIR src/tests)

	#set(TEST_SOURCES
		## C sources
		#${TESTS_DIR}/test.c
		#${SOURCE_DIR}/crt.c
		## C includes
	#)

	#add_executable(${TESTS} ${TEST_SOURCES}) 

	#target_link_directories(${TESTS} PRIVATE /usr/local/share/mingw64/lib)

	#target_link_libraries(${TESTS} cunit)
#endif()