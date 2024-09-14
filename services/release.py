#!/usr/bin/python3

import os
import os.path
import sys
import pdb
import time


def main():
    # 1. create a release/ folder
    print("[1] create a release/ folder")
    os.system("rm -rf release/")
    os.system("mkdir -p release/")
    print("=> ok\n")
    time.sleep(1)

    # 2. copy new someip service files to the target path
    print(f"[2] copy all new someip_service files to the release/ folder")
    if not os.path.exists("build"):
        print("[Error] please check the build/ folder again. you should run the script right under the SERVICE_NAME(SOME/IP app) directory")
        exit(1)

    cmd = "find ./build -type f"
    except_keywords = ['CMakeFiles', 'CMakeCache', 'Makefile', 'cmake_install']
    for kw in except_keywords:
        cmd += f"| grep -v {kw}"
    src_files = os.popen(cmd).read().strip().split("\n")
    for src_f in src_files:
        ret = os.system(f"cp -rf {src_f} release/")
        if ret != 0:
            print("[Error] error happened. please check the error.")
            exit(1)
    print("=> ok\n")
    time.sleep(1)

if __name__ == "__main__":
    main()
