#!/bin/bash -e

TRANSPORT_PROTOCOL=$1
APP_NAME=$(cat someip_service.prop | grep APP_NAME | awk -F= '{print $2}')

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
echo "  ${APP_NAME}_client  -----(copy)----->  ${APP_NAME}_client_$TRANSPORT_PROTOCOL"
echo "  ${APP_NAME}_server  -----(copy)----->  ${APP_NAME}_server_$TRANSPORT_PROTOCOL"
echo "--------------------------------------------------------------------------------------"
echo ""

cp -rf ${APP_NAME}_client ${APP_NAME}_client_$TRANSPORT_PROTOCOL
cp -rf ${APP_NAME}_server ${APP_NAME}_server_$TRANSPORT_PROTOCOL

# copy SOME/IP service conf file
cp -rf ../conf/client*.json.in .
cp -rf ../conf/server*.json.in .
cp -rf ../../../routing/* .

# copy SOME/IP service script file
cp -rf ../../../scripts/*.sh .
cp -rf ../../../scripts/*.py .

# copy someip_service.prop
cp -rf ../someip_service.prop .

