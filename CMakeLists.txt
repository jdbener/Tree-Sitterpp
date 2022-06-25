cmake_minimum_required(VERSION 3.8)
project(TreeSitter++ LANGUAGES CXX C)
# enable_testing()

set(CXX_STANDARD 20 REQUIRED)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20")

#Force colors in Ninja
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()


file(GLOB sources "parser/src/*.c" "parser/src/*.cc" "thirdparty/tree-sitter/lib/src/lib.c")
file(GLOB testSources "src/*.cpp")
set(includes "inc/" "parser/src" "thirdparty/tree-sitter/lib/src/" "thirdparty/tree-sitter/lib/include")

add_library(TreeSitter++ ${sources})
target_include_directories(TreeSitter++ PUBLIC ${includes})

add_executable(tspp ${testSources})
target_link_libraries(tspp PUBLIC TreeSitter++)