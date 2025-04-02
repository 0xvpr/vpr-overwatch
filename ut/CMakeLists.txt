include_directories(
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}
)

add_executable(
    ${PROJECT_NAME}-tests
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/parser.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/util.cpp
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/watcher.cpp
    test.cpp
    parser_test.cpp
    util_test.cpp
    watcher_test.cpp
)

set_target_properties(
    ${PROJECT_NAME}-tests
    PROPERTIES
        PREFIX vpr-
)
