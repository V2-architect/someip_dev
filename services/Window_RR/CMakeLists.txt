cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

# Include symbols, just in case we need to debug a crash
set(CMAKE_BUILD_TYPE Debug)

# service properties
set(SERVICE_NAME "Window_RR")
set(APP_CLIENT_NAME "${SERVICE_NAME}_client")
set(APP_SERVER_NAME "${SERVICE_NAME}_server")

# build dependencies
set(DEPS_PATH        "/home/jhshin/work/dependencies")
set(LIB_CAPI_CORE    "capicxx-core-runtime_3.2.0")
set(LIB_CAPI_SOMEIP  "capicxx-someip-runtime_3.2.0")
set(LIB_VSOMEIP      "vsomeip_3.3.0")

#############################################################

# define dependencies header files
include_directories(
    src-gen
    ${DEPS_PATH}/${LIB_CAPI_CORE}/include
    ${DEPS_PATH}/${LIB_CAPI_SOMEIP}/include
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
    ${DEPS_PATH}/${LIB_CAPI_CORE}/lib
    ${DEPS_PATH}/${LIB_CAPI_SOMEIP}/lib
    ${DEPS_PATH}/${LIB_VSOMEIP}/lib
)

#SOME/IP service client
add_executable(${APP_CLIENT_NAME}
	src/${APP_CLIENT_NAME}.cpp
	src-gen/v1/commonapi/${SERVICE_NAME}SomeIPProxy.cpp
	src-gen/v1/commonapi/${SERVICE_NAME}SomeIPDeployment.cpp
)
target_link_libraries(${APP_CLIENT_NAME} CommonAPI CommonAPI-SomeIP vsomeip3)

#SOME/IP service server
add_executable(${APP_SERVER_NAME}
	src/${APP_SERVER_NAME}.cpp
	src/${APP_SERVER_NAME}_stubimpl.cpp
	src-gen/v1/commonapi/${SERVICE_NAME}SomeIPStubAdapter.cpp
	src-gen/v1/commonapi/${SERVICE_NAME}SomeIPDeployment.cpp
)
target_link_libraries(${APP_SERVER_NAME} CommonAPI CommonAPI-SomeIP vsomeip3)

