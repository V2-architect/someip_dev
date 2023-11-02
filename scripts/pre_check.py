#!/usr/bin/python3

import os
import sys

def main(argv):
    # 01. check if /etc/commonapi.ini exists
    if not os.path.exists("/etc/commonapi.ini"):
        print("[Error] /etc/commonapi.ini file is not found")
        exit(1)

    # 02. check if lib exists in LD_LIBRARY_PATH
    ld_library_path = argv[0]
    for ld_path in ld_library_path.split(":"):
        if not os.path.exists(ld_path):
            print(f"[Error] {ld_path} foler is not found")
            exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("[Error] $ pre_check.py ${LD_LIBRARY_PATH}")
        exit(1)

    main(sys.argv[1:])

