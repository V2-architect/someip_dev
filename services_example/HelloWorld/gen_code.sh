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
echo "    HelloWorld_$1.fdepl ----(copy)----> HelloWorld.fdepl"
echo "-----------------------------------------------------------"
echo ""
cp ./fidl/HelloWorld_$1.fdepl ./fidl/HelloWorld.fdepl

# generate source files
CGEN_ROOT=/home/jhshin/work/tools/cgen
$CGEN_ROOT/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk ./fidl/HelloWorld.fidl
$CGEN_ROOT/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 ./fidl/HelloWorld.fdepl
