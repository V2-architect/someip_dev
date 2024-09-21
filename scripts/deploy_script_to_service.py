
import os

script_path = os.path.abspath(__file__)
script_dir = os.path.dirname(script_path)
os.chdir(script_dir)
target_files = os.popen("find . -maxdepth 1 -type f | grep -v ./deploy_script_to_service.py").read().strip().split("\n")

os.chdir("../services")
service_list = os.popen("ls -d */ | grep -v template").read().strip().split("\n")

# at services/
for service in service_list:
	for f in target_files:
		print(f"cp -rf ../scripts/{f} {service}")
		os.system(f"cp -rf ../scripts/{f} {service}")
