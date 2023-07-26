#!/bin/bash -e

TRANSPORT_PROTOCOL=$1

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
echo "  HelloWorldSomeIPClient  -----(copy)-----> HelloWorldSomeIPClient_$TRANSPORT_PROTOCOL"
echo "  HelloWorldSomeIPService -----(copy)-----> HelloWorldSomeIPService_$TRANSPORT_PROTOCOL"
echo "--------------------------------------------------------------------------------------"
echo ""

cp -rf HelloWorldSomeIPClient HelloWorldSomeIPClient_$TRANSPORT_PROTOCOL
cp -rf HelloWorldSomeIPService HelloWorldSomeIPService_$TRANSPORT_PROTOCOL

cp -rf ../conf/*.json.in .
cp -rf ../conf/*.json .
cp -rf ../../../scripts/*.sh .
