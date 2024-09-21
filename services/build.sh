#!/bin/bash -e

TRANSPORT_PROTOCOL=$1
SERVICE_NAME=$(cat someip_service.prop | grep SERVICE_NAME | awk -F= '{print $2}')

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
echo "  ${SERVICE_NAME}_client  -----(copy)----->  ${SERVICE_NAME}_client_$TRANSPORT_PROTOCOL"
echo "  ${SERVICE_NAME}_server  -----(copy)----->  ${SERVICE_NAME}_server_$TRANSPORT_PROTOCOL"
echo "--------------------------------------------------------------------------------------"
echo ""

cp -rf ${SERVICE_NAME}_client ${SERVICE_NAME}_client_$TRANSPORT_PROTOCOL
cp -rf ${SERVICE_NAME}_server ${SERVICE_NAME}_server_$TRANSPORT_PROTOCOL

# copy SOME/IP service conf file
cp -rf ../conf/client*.json.in .
cp -rf ../conf/server*.json.in .

# copy SOME/IP service script file
cp -rf ../../../scripts/*.sh .
cp -rf ../../../scripts/*.py .

# copy someip_service.prop
cp -rf ../someip_service.prop .

# time_interval
#cp -rf ../*_interval.txt .
