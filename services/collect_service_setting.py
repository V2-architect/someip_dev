
import os
import json
import pdb

'''
collect all "services" dict data in server.json into "out.json"
'''

server_json_files = os.popen("find */conf -name server.json.in").read().strip().split("\n")

service_infos = []
for server_json in server_json_files:
	if 'template' in server_json:
		continue
	server_info = json.loads(open(server_json).read())
	service_infos += server_info["services"]

with open("out.json", "w") as f:
	f.write(json.dumps(service_infos, indent=4))
	
