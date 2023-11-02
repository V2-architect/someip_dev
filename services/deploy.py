#!/usr/bin/python3

import os
import os.path
import sys
import pdb
import time


def main(someip_service_target_path):
    # 1. check if target path exists
    print("[1] target directory check")
    if not os.path.exists(someip_service_target_path):
        print(f"[Error] {someip_service_target_path} does not exists")
        exit(1)
    print("=> ok\n")
    time.sleep(1)

    # 2. rm all the files in the target path
    print(f"[2] remove all files in the target path ({someip_service_target_path})")
    os.system(f"rm -rf {someip_service_target_path}/*")
    print("=> ok\n")
    time.sleep(1)

    # 3. copy new someip service files to the target path
    print(f"[3] copy all new someip_service files to the target path ({someip_service_target_path})")
    cmd = "find ./build -type f"
    except_keywords = ['CMakeFiles', 'CMakeCache', 'Makefile', 'cmake_install']
    for kw in except_keywords:
        cmd += f"| grep -v {kw}"
    src_files = os.popen(cmd).read().strip().split("\n")
    for src_f in src_files:
        os.system(f"cp -rf {src_f} {someip_service_target_path}/")
    print("=> ok\n")
    time.sleep(1)

    # 4. print the target path and give the instruction to commit/push
    print("[4] deployment is done. please commit all & push")
    print("=> ok\n")
    time.sleep(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("[Error] $ deploy.py <SOMEIP_SERVICE_RUNTIME_TARGET_PATH>")
        exit(1)
    main(sys.argv[1])
