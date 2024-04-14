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

target_link_options(
    ${PROJECT_NAME}
    PRIVATE $<$<CXX_COMPILER_ID:GNU>:-s>
            $<$<CXX_COMPILER_ID:GNU>:-static>
)
