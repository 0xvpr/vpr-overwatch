include_directories( ${CMAKE_SOURCE_DIR}/src )

add_executable(
    ${PROJECT_NAME}-test
    ../src/parser.cpp
    ../src/util.cpp
    ../src/watcher.cpp
    test.cpp
    parser_test.cpp
    util_test.cpp
    watcher_test.cpp
)
