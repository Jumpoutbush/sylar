cmake_minimum_required(VERSION 3.0)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC
    sylar/log.cc
    sylar/util.cc
    sylar/config.cc
    )

add_library(sylar SHARED ${LIB_SRC})
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

include_directories(.)
include_directories(../include)
link_directories(../lib)

find_library(YAMLCPP yaml-cpp.)
message("***", ${YAMLCPP})

add_executable(test tests/test.cc)
add_dependencies(test sylar)
target_link_libraries(test sylar ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar ${YAMLCPP})

#add_executable(test_util tests/test_util.cc)
#add_dependencies(test_util sylar)
#target_link_libraries(test_util sylar)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
