#-*- encoding=utf-8 -*-
import os
import pdb

'''
(1) copy *.json file under service_tmp/ -> service/ (conf/, build/ release/)
(2) copy ../scripts/* -> service/ (build/, release/)
'''

SERVICE_NAMES = [
	"Collision", "Driving", "Intersection", "ObjectDetection", "SteeringWheel", 
	"TrafficLight", "Transmission", "VehicleAccel", "VehicleLocation", "VehiclePose", 
	"VehicleSpeed", "Logging"
]

print("[1] Update server.json.in, client.json.in -> {service}/conf,/build,/release")
# json file update
for svc in SERVICE_NAMES:
    target_path_list = [f"./{svc}/conf/", f"./{svc}/build/", f"./{svc}/release/"]
    for path in target_path_list:
        if os.path.exists(path):
            cmd = f"cp -rf ../services_tmp/{svc}/conf/* {path}"
            os.system(cmd)
            #print(cmd)

'''
print("[2] Update scripts/run_*.sh -> {service}/build,/release")
print("[2] Update scripts/run_*.sh -> routingmanager/")
# script update
for svc in SERVICE_NAMES:
    target_path_list = [f"./{svc}/build/", f"./{svc}/release/"]
    for path in target_path_list:
        if os.path.exists(path):
            cmd = f"cp -rf ../scripts/* {path}"
            os.system(cmd)
            #print(cmd)

os.system("cp -rf ../scripts/* ./routingmanager/")
'''
