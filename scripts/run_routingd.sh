#!/bin/bash -e

if [ -z "$1" ]; then
    echo "[Error] input the argument like below"
    echo "  $ $0 <HOST_IP>"
    echo "  $ $0 10.0.0.1"
    exit -1
fi

# get data from user input
SOMEIP_HOST_IP=$1
TRANSPORT_PROTOCOL=$2

DEV_MODE="n"
if [ "$(echo $(pwd) | grep someip_dev)" != "" ]; then
    DEV_MODE="y"
fi

# get SOME/IP service runtime information from someip_service.prop
APP_NAME=`cat someip_service.prop | grep APP_NAME | awk -F= '{print $2}'`
MULTICAST_IP=`cat someip_service.prop | grep MULTICAST_IP | awk -F= '{print $2}'`

# get env variable at runtime
CURR_SH_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
GIT_PROJECT_ROOT=`./get_git_path.py ${CURR_SH_PATH}`
BOOST_LIBRARY_PATH=${GIT_PROJECT_ROOT}/dependencies/boost_1_64_0/lib
CAPICXX_CORE_PATH=${GIT_PROJECT_ROOT}/dependencies/capicxx-core-runtime_3.2.0/lib
CAPICXX_SOMEIP_PATH=${GIT_PROJECT_ROOT}/dependencies/capicxx-someip-runtime_3.2.0/lib
VSOMEIP_PATH=${GIT_PROJECT_ROOT}/dependencies/vsomeip_3.3.0/lib
APP_LD_LIBRARY_PATH=${BOOST_LIBRARY_PATH}:${CAPICXX_CORE_PATH}:${CAPICXX_SOMEIP_PATH}:${VSOMEIP_PATH}

APP_ROOT=${GIT_PROJECT_ROOT}/services/${APP_NAME}
if [ "${DEV_MODE}" == "y" ]; then
    APP_ROOT=${GIT_PROJECT_ROOT}/services/${APP_NAME}/build
fi

# check prerequisite
./pre_check.py ${APP_LD_LIBRARY_PATH}

CONF_FILE_TEMPLATE=${APP_ROOT}/routingmanagerd.json.in
CONF_FILE=${APP_ROOT}/routingmanagerd.json

echo "==========================================="
echo "============= SOME/IP Client =============="
echo "==========================================="

echo "GIT_PROJECT_ROOT  : "${GIT_PROJECT_ROOT}
echo "APP_ROOT          : "${APP_ROOT}
echo "SOMEIP_HOST_IP    : "${SOMEIP_HOST_IP}
echo "MULTICAST_IP      : "${MULTICAST_IP}
echo "TRANSPORT_PROTOCOL: "${TRANSPORT_PROTOCOL}
echo "LD_LIBRARY_PATH   : "${APP_LD_LIBRARY_PATH}

sed "s/@SOMEIP_HOST_IP@/${SOMEIP_HOST_IP}/g" $CONF_FILE_TEMPLATE > $CONF_FILE

LD_LIBRARY_PATH=$APP_LD_LIBRARY_PATH \
    VSOMEIP_CONFIGURATION=$CONF_FILE \
    ${APP_ROOT}/routingmanagerd


