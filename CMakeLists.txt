cmake_minimum_required (VERSION 3.7)
project (CharGuyChess)

add_compile_options(-std=c++11 -Wall -Werror)

set(APP_NAME cgc)
set(APP_LIB_NAME ${APP_NAME}lib)

add_subdirectory(src)

option(COMPILE_TESTS "Compile the tests" OFF)
if(COMPILE_TESTS)
  add_subdirectory(tests)
endif(COMPILE_TESTS)