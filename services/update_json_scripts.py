import os

SERVICE_NAMES = ["Collision", "Driving", "Intersection", "ObjectDetection", "SteeringWheel", "TrafficLight", "Transmission", "VehicleAccel", "VehicleLocation", "VehiclePose", "VehicleSpeed"]

# json file update
for svc in SERVICE_NAMES:
    target_path_list = [f"./{svc}/conf/", f"./{svc}/build/", f"./{svc}/release/"]
    for path in target_path_list:
        if os.path.exists(path):
            cmd = f"cp -rf ../services_tmp/{svc}/conf/* {path}"
            os.system(cmd)
            #print(cmd)

# script update
for svc in SERVICE_NAMES:
    target_path_list = [f"./{svc}/build/", f"./{svc}/release/"]
    for path in target_path_list:
        if os.path.exists(path):
            cmd = f"cp -rf ../scripts/* {path}"
            os.system(cmd)
            #print(cmd)

os.system("cp -rf ../scripts/* ./routingmanager/")
