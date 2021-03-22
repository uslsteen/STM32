#!/usr/bin/env python3

str = None
with open("quest.txt", "r") as f:
    str = f.read()

spl = str.split('\n')

for el in spl:
    print(f"\\subsection{{{el}}}")
