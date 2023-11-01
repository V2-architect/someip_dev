#!/bin/bash -e

TRANSPORT_PROTOCOL=$1
SOMEIP_SERVICE="MethodApp"

if [ -z "$TRANSPORT_PROTOCOL" ]; then
    echo "[Error] input the protocol"
    echo "  $ $0 tcp"
    echo "  $ $0 udp"
    exit -1
fi

echo "Start to build.."
mkdir -p build
cd build
cmake ..
make -j4
echo "Build done"

echo "--------------------------------------------------------------------------------------"
echo "  ${SOMEIP_SERVICE}_client  -----(copy)----->  ${SOMEIP_SERVICE}_client_$TRANSPORT_PROTOCOL"
echo "  ${SOMEIP_SERVICE}_server  -----(copy)----->  ${SOMEIP_SERVICE}_server_$TRANSPORT_PROTOCOL"
echo "--------------------------------------------------------------------------------------"
echo ""

cp -rf ${SOMEIP_SERVICE}_client ${SOMEIP_SERVICE}_client_$TRANSPORT_PROTOCOL
cp -rf ${SOMEIP_SERVICE}_server ${SOMEIP_SERVICE}_server_$TRANSPORT_PROTOCOL

cp -rf ../conf/*.json.in .
cp -rf ../../../scripts/*.sh .
