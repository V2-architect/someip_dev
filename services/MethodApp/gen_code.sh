#!/bin/bash

TRANSPORT_PROTOCOL=$1

if [ -z "${TRANSPORT_PROTOCOL}" ]; then
    echo "[Error] please input the protocol"
    echo "   $ $0 tcp"
    echo "   $ $0 udp"
    exit -1
fi

rm -rf src-gen/*

# copy corresponding fdepl file to the target file
echo "-----------------------------------------------------------"
echo "    MethodApp_$1.fdepl ----(copy)----> MethodApp.fdepl"
echo "-----------------------------------------------------------"
echo ""
cp ./fidl/MethodApp_$1.fdepl ./fidl/MethodApp.fdepl

# generate source files
CGEN_ROOT=/home/jhshin/work/tools/cgen
$CGEN_ROOT/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk ./fidl/MethodApp.fidl
$CGEN_ROOT/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 ./fidl/MethodApp.fdepl
