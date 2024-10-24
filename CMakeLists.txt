cmake_minimum_required(VERSION 3.0)
project(sylar)

include(cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

set(LIB_SRC
    sylar/log.cc
    sylar/util.cc
    sylar/config.cc
    sylar/thread.cc
    sylar/fiber.cc
    sylar/scheduler.cc
    sylar/iomanager.cc
    sylar/timer.cc
    sylar/hook.cc
    sylar/fd_manager.cc
    )

add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(sylar)
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")


include_directories(.)
include_directories(../include)
link_directories(../lib)

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} sylar)
#set(LIBS ${LIBS} dl)
#message("***", ${YAMLCPP})

set(LIB_LIB
        sylar
        dl
        pthread
        yaml-cpp
    )

# add_executable(test tests/test.cc)
# add_dependencies(test sylar)
# force_redefine_file_macro_for_sources(test)
# target_link_libraries(test ${LIB_LIB})

# add_executable(test_config tests/test_config.cc)
# add_dependencies(test_config sylar)
# force_redefine_file_macro_for_sources(test_config)
# target_link_libraries(test_config sylar ${LIB_LIB})

# add_executable(test_thread tests/test_thread.cc)
# add_dependencies(test_thread sylar)
# force_redefine_file_macro_for_sources(test_thread)
# target_link_libraries(test_thread sylar ${LIB_LIB})

# add_executable(test_util tests/test_util.cc)
# add_dependencies(test_util sylar)
# force_redefine_file_macro_for_sources(test_util)
# target_link_libraries(test_util sylar ${LIB_LIB})

# add_executable(test_fiber tests/test_fiber.cc)
# add_dependencies(test_fiber sylar)
# force_redefine_file_macro_for_sources(test_fiber)
# target_link_libraries(test_fiber sylar ${LIB_LIB})

# add_executable(test_scheduler tests/test_scheduler.cc)
# add_dependencies(test_scheduler sylar)
# force_redefine_file_macro_for_sources(test_scheduler)
# target_link_libraries(test_scheduler sylar ${LIB_LIB})

# add_executable(test_iomanager tests/test_iomanager.cc)
# add_dependencies(test_iomanager sylar)
# force_redefine_file_macro_for_sources(test_iomanager)
# target_link_libraries(test_iomanager sylar ${LIB_LIB})

add_executable(test_hook tests/test_hook.cc)
add_dependencies(test_hook sylar)
force_redefine_file_macro_for_sources(test_hook)
target_link_libraries(test_hook sylar ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
