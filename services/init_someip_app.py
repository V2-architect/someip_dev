import argparse
import os
import logging
import json
import pdb
logging.basicConfig(level=logging.INFO, format='[AUTO-IDS][%(asctime)s] %(message)s', datefmt='%y%m%d-%H%M%S')

def main(svc_name, svc_type):
	curr_path = os.getcwd()

	# [1] copy template to the service folder
	logging.info("[1] Create new Service foler and fill with draft files in the template folder")
	os.system(f"rm -rf {svc_name}")
	os.makedirs(svc_name, exist_ok=True)

	os.system(f"cp -rf template/SOMEIP_common/* {svc_name}/")
	os.system(f"cp -rf template/SOMEIP_{svc_type}/* {svc_name}/")

	os.chdir(f"{svc_name}")
	for script in ['build.sh', 'gen_code.sh', 'deploy.py', 'release.py']:
		os.system(f"ln -sf ../{script} ./{script}")
	os.chdir(curr_path)


	# [2] replace template variables with service specific term
	logging.info("[2] replace template variables with service specific term")
	service_spec = json.loads(open("template/service_info/someip_service_spec.json").read())
	service_info = service_spec[svc_name]

	# [2-1] file name change
	os.chdir(f"{svc_name}")
	files = os.popen(f'find . -name "SERVICE_NAME*"').read().strip().split("\n")
	for f in files:
		new_f = f.replace("SERVICE_NAME", svc_name)
		#logging.info(f"mv {f} {new_f}")
		os.system(f"mv {f} {new_f}")

	# [2-2] file content change
	files = os.popen("find . -type f").read().strip().split("\n")
	replace_target = [
		"EVENTGROUP_MULTICAST_IP",
		"EVENTGROUP_MULTICAST_PORT_NUM",
		"EVENTGROUP_ID",
		"EVENT_ID",
		"EVENT_NAME",
		"INSTANCE_ID",
		"METHOD_ID",
		"METHOD_NAME",
		"SERVICE_ID",
		"SERVICE_NAME",
		"TCP_PORT_NUM",
		"UDP_PORT_NUM",
		"UNIX_DOMAIN_SOCKET_PATH"
	]

	for f in files:
		f_out = ""
		if f.endswith("fidl.in") or f.endswith("fdepl.in"):
			f_out = f.replace(".in", "")
			os.system(f"mv {f} {f_out}")
			f = f_out

		for target in replace_target:
			service_text = service_info[target]

			# [NOTE] exceptional logic...
			if target != 'EVENT_ID' and target.endswith("_ID"):
				service_text = f"0x{service_text.zfill(4)}"

			#if target == 'SERVICE_NAME':
			#	pdb.set_trace()
			#logging.info(f"sed -i s,@{target}@,{service_text},g {f}")
			os.system(f"sed -i s,@{target}@,{service_text},g {f}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    
    parser.add_argument("-n", "--service-name", required=True, type=str, help="Name of the app")
    parser.add_argument("-t", "--service-type", required=True, type=str, choices=["method", "event"], help="Type of the app (method or event)")

    args = parser.parse_args()

    svc_name = args.service_name
    svc_type = args.service_type

    #logging.info(f"Creating {svc_type} app {svc_name}")
    main(svc_name, svc_type)
