cmake_minimum_required(VERSION 3.0)
project(sylar)

include(cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

set(LIB_SRC
    sylar/address.cc
    sylar/application.cc
    sylar/bytearray.cc
    sylar/config.cc
    sylar/daemon.cc
    sylar/env.cc
    sylar/hook.cc
    sylar/http.cc
    sylar/fd_manager.cc
    sylar/fiber.cc
    sylar/iomanager.cc
    sylar/log.cc
    sylar/mutex.cc
    sylar/scheduler.cc
    sylar/socket.cc
    sylar/stream.cc
    sylar/tcp_server.cc
    sylar/thread.cc
    sylar/timer.cc
    sylar/util.cc

    sylar/http/http11_parser.rl.cc
    sylar/http/httpclient_parser.rl.cc
    sylar/http/http_connection.cc
    sylar/http/http_parser.cc
    sylar/http/http_server.cc
    sylar/http/http_session.cc
    sylar/http/servlet.cc
    
    sylar/streams/socket_stream.cc
    sylar/streams/zlib_stream.cc
    )

    ragelmaker(sylar/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar/http)
    ragelmaker(sylar/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar/http)
    ragelmaker(sylar/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar)

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

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

set(LIB_LIB
        sylar
        dl
        pthread
        yaml-cpp
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        event


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

# add_executable(test_hook tests/test_hook.cc)
# add_dependencies(test_hook sylar)
# force_redefine_file_macro_for_sources(test_hook)
# target_link_libraries(test_hook sylar ${LIB_LIB})

# add_executable(test_address tests/test_address.cc)
# add_dependencies(test_address sylar)
# force_redefine_file_macro_for_sources(test_address)
# target_link_libraries(test_address sylar ${LIB_LIB})

# add_executable(test_socket tests/test_socket.cc)
# add_dependencies(test_socket sylar)
# force_redefine_file_macro_for_sources(test_socket)
# target_link_libraries(test_socket sylar ${LIB_LIB})

# add_executable(test_http tests/test_http.cc)
# add_dependencies(test_http sylar)
# force_redefine_file_macro_for_sources(test_http)
# target_link_libraries(test_http sylar ${LIB_LIB})

# add_executable(test_http_parser tests/test_http_parser.cc)
# add_dependencies(test_http_parser sylar)
# force_redefine_file_macro_for_sources(test_http_parser)
# target_link_libraries(test_http_parser sylar ${LIB_LIB})

# add_executable(test_tcp_server tests/test_tcp_server.cc)
# add_dependencies(test_tcp_server sylar)
# force_redefine_file_macro_for_sources(test_tcp_server)
# target_link_libraries(test_tcp_server sylar ${LIB_LIB})

# add_executable(echo_server examples/echo_server.cc)
# add_dependencies(echo_server sylar)
# force_redefine_file_macro_for_sources(echo_server)
# target_link_libraries(echo_server sylar ${LIB_LIB})

# add_executable(test_http_server tests/test_http_server.cc)
# add_dependencies(test_http_server sylar)
# force_redefine_file_macro_for_sources(test_http_server)
# target_link_libraries(test_http_server sylar ${LIB_LIB})

# add_executable(test_http_connection tests/test_http_connection.cc)
# add_dependencies(test_http_connection sylar)
# force_redefine_file_macro_for_sources(test_http_connection)
# target_link_libraries(test_http_connection sylar ${LIB_LIB})

# add_executable(test_daemon tests/test_daemon.cc)
# add_dependencies(test_daemon sylar)
# force_redefine_file_macro_for_sources(test_daemon)
# target_link_libraries(test_daemon sylar ${LIB_LIB})

# add_executable(test_env tests/test_env.cc)
# add_dependencies(test_env sylar)
# force_redefine_file_macro_for_sources(test_env)
# target_link_libraries(test_env sylar ${LIB_LIB})

add_executable(test_application tests/test_application.cc)
add_dependencies(test_application sylar)
force_redefine_file_macro_for_sources(test_application)
target_link_libraries(test_application sylar ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
