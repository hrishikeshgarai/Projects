#!/bin/python

import sys

def pair(n,c):
    c.sort()
    i = 0
    pairs = 0
    while i < n-1:
        if c[i] == c[i+1]:
            pairs += 1
            i += 2
        else:
            i += 1
    return pairs
""""
    while i < len(c)-1:
        if c[i] == c[i+1]:
            c.pop(i)
            c.pop(i)
            pairs += 1
        else:
            i+=1
"""
n = int(raw_input().strip())
c = map(int,raw_input().strip().split(' '))
print pair(n,c)