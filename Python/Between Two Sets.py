#!/bin/python

import sys

def number(n,m,a,b):
    multiple=factor=total=0
    for i in range(1,101):
        for j in a:
            if i%j!=0:
                factor = 0
                break
            else:
                factor = 1
        for j in b:
            if j%i!=0:
                multiple = 0
                break
            else:
                multiple = 1
        if factor == 1 and multiple == 1:
            total += 1
    return total

n,m = raw_input().strip().split(' ')
n,m = [int(n),int(m)]
a = map(int,raw_input().strip().split(' '))
b = map(int,raw_input().strip().split(' '))
print number(n,m,a,b)