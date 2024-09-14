import argparse
import os
import logging
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
	for script in ['build.sh', 'gen_code.sh', 'deploy.py']:
		os.system(f"ln -sf ../{script} ./{script}")
	os.chdir(curr_path)


	# [2] replace template variables with service specific term
	# [2-1] file name change
	os.chdir(f"{svc_name}")
	files = os.popen(f'find . -name "SERVICE_NAME*"').read().strip().split("\n")
	for f in files:
		new_f = f.replace("SERVICE_NAME", svc_name)
		#logging.info(f"mv {f} {new_f}")
		os.system(f"mv {f} {new_f}")

	# [2-2] file content change
	files = os.popen("find . -type f").read().strip().split("\n")
	for f in files:
		sed s/@SERVICE_NAME@/

	
	


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    
    parser.add_argument("-n", "--service-name", required=True, type=str, help="Name of the app")
    parser.add_argument("-t", "--service-type", required=True, type=str, choices=["method", "event"], help="Type of the app (method or event)")

    args = parser.parse_args()

    svc_name = args.service_name
    svc_type = args.service_type

    #logging.info(f"Creating {svc_type} app {svc_name}")
    main(svc_name, svc_type)
