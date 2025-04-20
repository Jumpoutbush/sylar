cmake_minimum_required(VERSION 3.0)
project(frame)

include(cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

set(LIB_SRC
    frame/address.cc
    frame/application.cc
    frame/bytearray.cc
    frame/config.cc
    frame/daemon.cc
    frame/env.cc
    frame/hook.cc
    frame/http.cc
    frame/fd_manager.cc
    frame/fiber.cc
    frame/iomanager.cc
    frame/log.cc
    frame/mutex.cc
    frame/scheduler.cc
    frame/socket.cc
    frame/stream.cc
    frame/tcp_server.cc
    frame/thread.cc
    frame/timer.cc
    frame/util.cc
    #frame/worker.cc

    frame/http/http11_parser.rl.cc
    frame/http/httpclient_parser.rl.cc
    frame/http/http_connection.cc
    frame/http/http_parser.cc
    frame/http/http_server.cc
    frame/http/http_session.cc
    frame/http/servlet.cc
    
    frame/streams/socket_stream.cc
    frame/streams/zlib_stream.cc

    frame/mprpc/rpcprovider.cc
    frame/mprpc/mprpcapplication.cc
    )

    ragelmaker(frame/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/frame/http)
    ragelmaker(frame/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/frame/http)
    ragelmaker(frame/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/frame)

add_library(frame SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(frame)
#add_library(frame_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (frame_static PROPERTIES OUTPUT_NAME "frame")


include_directories(.)
include_directories(../include)
link_directories(../lib)

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} frame)
#set(LIBS ${LIBS} dl)
#message("***", ${YAMLCPP})

# find_package(Protobuf)
# if(Protobuf_FOUND)
#     include_directories(${Protobuf_INCLUDE_DIRS})
# endif()

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

set(LIB_LIB
        frame
        dl
        pthread
        yaml-cpp
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        event


    )

# add_executable(test tests/test.cc)
# add_dependencies(test frame)
# force_redefine_file_macro_for_sources(test)
# target_link_libraries(test ${LIB_LIB})

# add_executable(test_config tests/test_config.cc)
# add_dependencies(test_config frame)
# force_redefine_file_macro_for_sources(test_config)
# target_link_libraries(test_config frame ${LIB_LIB})

# add_executable(test_thread tests/test_thread.cc)
# add_dependencies(test_thread frame)
# force_redefine_file_macro_for_sources(test_thread)
# target_link_libraries(test_thread frame ${LIB_LIB})

# add_executable(test_util tests/test_util.cc)
# add_dependencies(test_util frame)
# force_redefine_file_macro_for_sources(test_util)
# target_link_libraries(test_util frame ${LIB_LIB})

# add_executable(test_fiber tests/test_fiber.cc)
# add_dependencies(test_fiber frame)
# force_redefine_file_macro_for_sources(test_fiber)
# target_link_libraries(test_fiber frame ${LIB_LIB})

add_executable(test_scheduler tests/test_scheduler.cc)
add_dependencies(test_scheduler frame)
force_redefine_file_macro_for_sources(test_scheduler)
target_link_libraries(test_scheduler frame ${LIB_LIB})

add_executable(test_iomanager tests/test_iomanager.cc)
add_dependencies(test_iomanager frame)
force_redefine_file_macro_for_sources(test_iomanager)
target_link_libraries(test_iomanager frame ${LIB_LIB})

# add_executable(test_hook tests/test_hook.cc)
# add_dependencies(test_hook frame)
# force_redefine_file_macro_for_sources(test_hook)
# target_link_libraries(test_hook frame ${LIB_LIB})

# add_executable(test_address tests/test_address.cc)
# add_dependencies(test_address frame)
# force_redefine_file_macro_for_sources(test_address)
# target_link_libraries(test_address frame ${LIB_LIB})

# add_executable(test_socket tests/test_socket.cc)
# add_dependencies(test_socket frame)
# force_redefine_file_macro_for_sources(test_socket)
# target_link_libraries(test_socket frame ${LIB_LIB})

# add_executable(test_http tests/test_http.cc)
# add_dependencies(test_http frame)
# force_redefine_file_macro_for_sources(test_http)
# target_link_libraries(test_http frame ${LIB_LIB})

# add_executable(test_http_parser tests/test_http_parser.cc)
# add_dependencies(test_http_parser frame)
# force_redefine_file_macro_for_sources(test_http_parser)
# target_link_libraries(test_http_parser frame ${LIB_LIB})

# add_executable(test_tcp_server tests/test_tcp_server.cc)
# add_dependencies(test_tcp_server frame)
# force_redefine_file_macro_for_sources(test_tcp_server)
# target_link_libraries(test_tcp_server frame ${LIB_LIB})

# add_executable(echo_server examples/echo_server.cc)
# add_dependencies(echo_server frame)
# force_redefine_file_macro_for_sources(echo_server)
# target_link_libraries(echo_server frame ${LIB_LIB})

# add_executable(test_http_server tests/test_http_server.cc)
# add_dependencies(test_http_server frame)
# force_redefine_file_macro_for_sources(test_http_server)
# target_link_libraries(test_http_server frame ${LIB_LIB})

# add_executable(test_http_connection tests/test_http_connection.cc)
# add_dependencies(test_http_connection frame)
# force_redefine_file_macro_for_sources(test_http_connection)
# target_link_libraries(test_http_connection frame ${LIB_LIB})

# add_executable(test_daemon tests/test_daemon.cc)
# add_dependencies(test_daemon frame)
# force_redefine_file_macro_for_sources(test_daemon)
# target_link_libraries(test_daemon frame ${LIB_LIB})

# add_executable(test_env tests/test_env.cc)
# add_dependencies(test_env frame)
# force_redefine_file_macro_for_sources(test_env)
# target_link_libraries(test_env frame ${LIB_LIB})

# add_executable(test_application tests/test_application.cc)
# add_dependencies(test_application frame)
# force_redefine_file_macro_for_sources(test_application)
# target_link_libraries(test_application frame ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
