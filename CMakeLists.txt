cmake_minimum_required(VERSION 3.20)
find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    MESSAGE("CCACHE support enabled")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Release")

set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)

FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY "https://github.com/fmtlib/fmt"
    GIT_TAG fc5e59fe4a27c8589ba662ffea3b285a8f9aaff7
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmtlib)

FetchContent_Declare(
    argh
    GIT_REPOSITORY "https://github.com/adishavit/argh"
    GIT_TAG 39b9a00046143f6b300dcf98ea989486cf62097d
    GIT_PROGRESS TRUE
)
FetchContent_Populate(argh)
include_directories(${argh_SOURCE_DIR})

include(cmake/Utilities.cmake)

add_subdirectory(PairwiseSetDiff)
