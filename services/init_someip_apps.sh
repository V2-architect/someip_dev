#!/bin/bash
echo "Init Collision SOME/IP Service"
python3 init_someip_app.py -t event -n Collision
sleep 1

echo "Init Driving SOME/IP Service"
python3 init_someip_app.py -t event -n Driving
sleep 1

echo "Init Intersection SOME/IP Service"
python3 init_someip_app.py -t event -n Intersection
sleep 1

echo "Init ObjectDetection SOME/IP Service"
python3 init_someip_app.py -t event -n ObjectDetection
sleep 1

echo "Init SteeringWheel SOME/IP Service"
python3 init_someip_app.py -t event -n SteeringWheel
sleep 1

echo "Init TrafficLight SOME/IP Service"
python3 init_someip_app.py -t event -n TrafficLight
sleep 1

echo "Init Transmission SOME/IP Service"
python3 init_someip_app.py -t event -n Transmission
sleep 1

echo "Init VehicleAccel SOME/IP Service"
python3 init_someip_app.py -t event -n VehicleAccel
sleep 1

echo "Init VehicleLocation SOME/IP Service"
python3 init_someip_app.py -t event -n VehicleLocation
sleep 1

echo "Init VehiclePose SOME/IP Service"
python3 init_someip_app.py -t event -n VehiclePose
sleep 1



