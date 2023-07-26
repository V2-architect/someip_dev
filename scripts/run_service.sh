#!/bin/bash

if [ -z "$1" -o -z "$2" ]; then
    echo "[Error] input the argument like below"
    echo "  $ $0 <IP_ADDR> <TRANS_PROTOCOL> [<APP_NAME>]"
    echo "  $ $0 10.0.0.101 tcp"
    echo "  $ $0 10.0.0.101 udp"
    echo "  $ $0 10.0.0.101 tcp HelloWorld"
    echo "  $ $0 10.0.0.101 udp HelloWorld"
    exit -1
fi

SOMEIP_HOST_IP=$1
TRANSPORT_PROTOCOL=$2
APP_NAME="HelloWorld"
if [ ! -z "$3" ]; then
    APP_NAME="$3"
fi

APP_ROOT="/root/someip/services/"$APP_NAME
CONF_FILE=$APP_ROOT/service_$TRANSPORT_PROTOCOL.json

echo "APP_ROOT: "$APP_ROOT
echo "SOMEIP_HOST_IP: "$1
echo "TRANSPORT_PROTOCOL: "$2

sed "s/@SOMEIP_HOST_IP@/$1/g" $CONF_FILE.in > $CONF_FILE

VSOMEIP_CONFIGURATION=$CONF_FILE \
	VSOMEIP_APPLICATION_NAME=$APP_NAME \
	$APP_ROOT/${APP_NAME}SomeIPService_$TRANSPORT_PROTOCOL


