#!/bin/bash

if [ -z "$1" ]; then
    echo "[Error] input the argument like below"
    echo "  $ $0 <IP_ADDR>"
    echo "  $ $0 10.0.0.101"
    echo "  $ $0 10.0.0.102"
    exit -1
fi

SOMEIP_HOST_IP=$1
APP_ROOT="/root/someip/routing"
ROUTINGD=$APP_ROOT/routingmanagerd
CONF_FILE=$APP_ROOT/routingmanagerd.json

echo "APP_ROOT: "$APP_ROOT
echo "SOMEIP_HOST_IP: "$1

sed "s/@SOMEIP_HOST_IP@/$1/g" $CONF_FILE.in > $CONF_FILE

VSOMEIP_CONFIGURATION=$CONF_FILE $ROUTINGD

