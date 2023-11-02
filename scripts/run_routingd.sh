#!/bin/bash

if [ -z "$1" -o -z "$2" ]; then
    echo "[Error] input the argument like below"
    echo "  $ $0 <HOST_IP> <TRANS_PROTOCOL>"
    echo "  $ $0 10.0.0.1 tcp"
    echo "  $ $0 10.0.0.1 udp"
    exit -1
fi

# get data from user input
SOMEIP_HOST_IP=$1
TRANSPORT_PROTOCOL=$2

# get routingmanagerd runtime information from someip_service.prop
ROUTINGD_ROOT=`cat someip_service.prop | grep ROUTINGD_ROOT | awk -F= '{print $2}'`

ROUTINGD=$ROUTINGD_ROOT/routingmanagerd
CONF_FILE=$ROUTINGD_ROOT/routingmanagerd.json

echo "SOMEIP_HOST_IP: "$SOMEIP_HOST_IP
echo "ROUTINGD_ROOT: "$ROUTINGD_ROOT
echo "ROUTINGD_CONF_FILE: "$CONF_FILE

sed "s/@SOMEIP_HOST_IP@/$SOMEIP_HOST_IP/g" ./routingmanager/$CONF_FILE.in > $CONF_FILE

VSOMEIP_CONFIGURATION=$CONF_FILE $ROUTINGD

