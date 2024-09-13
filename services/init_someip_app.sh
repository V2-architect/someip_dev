#!/bin/bash

SOMEIP_APP_NAME=$1

# create the directory for new SOME/IP app
cp -rf template $SOMEIP_APP_NAME

# generate SOME/IP service interface based on service interface spec
cd $SOMEIP_APP_NAME
python3 gen_service_interface.py



