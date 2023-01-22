# Set compilers
set(CMAKE_CXX_COMPILER /bin/x86_64-w64-mingw32-g++-posix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compile flags
set(CMAKE_CXX_FLAGS "-O3 -s -static -Wall -Wextra -Wshadow -Wpedantic -Wconversion -fconcepts -ffast-math -funroll-loops") 
