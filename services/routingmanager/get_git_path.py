#!/usr/bin/python3

import os
import sys

def main(input_path):
    curr_path = input_path
    if not os.path.exists(curr_path):
        print(f"[Error] {curr_path} is not found")
        exit(1)

    os.chdir(curr_path)
    while not os.path.exists(".git"):
        os.chdir("..")
        if os.getcwd() == "/":
            print(f"[Error] git root path is not found")
            exit(1)
    else:
        print(os.getcwd())

    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("[Error] $ get_git_path.py ${CURR_PATH}")
        exit(1)
    main(sys.argv[1])

