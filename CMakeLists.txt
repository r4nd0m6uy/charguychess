cmake_minimum_required (VERSION 3.2)
project (CharGuyChess)

set (CGC_VERSION_MAJOR 0)
set (CGC_VERSION_MINOR 0)
set (CGC_VERSION_BUGFIX 0)
exec_program(git ${CMAKE_SOURCE_DIR} ARGS "describe" OUTPUT_VARIABLE CGC_VERSION_GIT )
configure_file (
  "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/version.hpp"
)

add_compile_options(-std=c++11 -Wall -Werror)

set(APP_NAME cgc)
set(APP_LIB_NAME ${APP_NAME}lib)

add_subdirectory(src)

option(COMPILE_TESTS "Compile the tests" OFF)
if(COMPILE_TESTS)
  add_subdirectory(tests)
endif(COMPILE_TESTS)
