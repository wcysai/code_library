#!/usr/bin/python3
import re, sys, hashlib

for line in sys.stdin.read().strip().split("\n") :
    print(hashlib.md5(re.sub(r'\s|//.*', '', line).encode('utf8')).hexdigest()[-4:], line)
