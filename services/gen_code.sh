#!/bin/bash

TRANSPORT_PROTOCOL=$1
SERVICE_NAME=$(cat someip_service.prop | grep SERVICE_NAME | awk -F= '{print $2}')

CURR_SH_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
GIT_PROJECT_ROOT=`../../scripts/get_git_path.py ${CURR_SH_PATH}`
CGEN_ROOT=${GIT_PROJECT_ROOT}/tools/cgen


if [ -z "${TRANSPORT_PROTOCOL}" ]; then
    echo "[Error] please input the protocol"
    echo "   $ $0 tcp"
    echo "   $ $0 udp"
    exit -1
fi

rm -rf src-gen/*

# copy corresponding fdepl file to the target file
echo "-----------------------------------------------------------"
echo "    ${SERVICE_NAME}_${TRANSPORT_PROTOCOL}.fdepl ----(copy)----> ${SERVICE_NAME}.fdepl"
echo "-----------------------------------------------------------"
echo ""
cp ./fidl/${SERVICE_NAME}_${TRANSPORT_PROTOCOL}.fdepl ./fidl/${SERVICE_NAME}.fdepl

# generate source files
$CGEN_ROOT/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk ./fidl/${SERVICE_NAME}.fidl
$CGEN_ROOT/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 ./fidl/${SERVICE_NAME}.fdepl
