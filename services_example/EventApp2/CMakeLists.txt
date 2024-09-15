cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

# Include symbols, just in case we need to debug a crash
set(CMAKE_BUILD_TYPE Debug)

# service properties
set(SERVICE_NAME "EventApp2")
set(APP_CLIENT_NAME "${SERVICE_NAME}_client")
set(APP_SERVER_NAME "${SERVICE_NAME}_server")

# build dependencies
set(DEPS_PATH        "/home/jhshin/work/dependencies")
set(LIB_VSOMEIP      "vsomeip_3.3.0")

#############################################################

# define dependencies header files
include_directories(
    ${DEPS_PATH}/${LIB_VSOMEIP}/include
)

# CMake needs the policy set to avoid warning about
# how to handle a relative path for linking.
# Then we set link search path relative to the source
# dir (thus reaching the locally built libraries we created)
# - Gunnar
cmake_policy(SET CMP0015 NEW)

# define dependencies lib files
link_directories(
    ${DEPS_PATH}/${LIB_VSOMEIP}/lib
)

#SOME/IP service client
add_executable(${APP_CLIENT_NAME}
	src/${APP_CLIENT_NAME}.cpp
)
target_link_libraries(${APP_CLIENT_NAME} vsomeip3)

#SOME/IP service server
add_executable(${APP_SERVER_NAME}
	src/${APP_SERVER_NAME}.cpp
)
target_link_libraries(${APP_SERVER_NAME} vsomeip3)

