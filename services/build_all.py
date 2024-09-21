
import os
import pdb

script_path = os.path.abspath(__file__)
script_dir = os.path.dirname(script_path)
os.chdir(script_dir)

service_list = os.popen("ls -d */ | grep -v template | grep -v routingmanager").read().strip().split("\n")

for service in service_list:
	os.chdir(os.path.join(script_dir, service))

	if os.system("./gen_code.sh udp") != 0:
		print("[Error] gen_code.sh udp error")
		exit(-1)

	if os.system("./build.sh udp") != 0:
		print("[Error] gen_code.sh udp error")
		exit(-1)

	if os.system("./release.py udp") != 0:
		print("[Error] ./release.py error")
		exit(-1)

