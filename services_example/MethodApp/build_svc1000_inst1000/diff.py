#!/usr/bin/python3

import os
import sys
import pdb

dir1 = sys.argv[1]
dir2 = sys.argv[2]

f_list1 = os.popen(f"find {dir1} -type f").read().strip().split('\n')
f_list2 = os.popen(f"find {dir2} -type f").read().strip().split('\n')

# [1] file list match
filename_list1 = set([f.split('/')[-1] for f in f_list1])
filename_list2 = set([f.split('/')[-1] for f in f_list2])

rst1 = filename_list1 - filename_list2
rst2 = filename_list2 - filename_list1

if bool(rst1) or bool(rst2):
    print("file list is not matched btw new_version and old_version")
    print('\n'.join(list(rst1)))
    print('\n'.join(list(rst2)))
    exit(-1)

# [2] diff check
for i, f1 in enumerate(f_list1):
    cmd = 'diff %s %s' % (f1, f_list2[i])
    ret = os.system(cmd)
    if bool(ret):
        print(f"[O] diff is occured -> {f1}")



