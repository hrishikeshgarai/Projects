#!/bin/python

import sys

def growth(a):
    res = ""
    for i in a:
        height = 1
        for j in range(1,i+1):
            if j%2==0:
                height+=1
            else:
                height*=2
        res = res + str(height)+ "\n"
    return res        
t = int(raw_input().strip())
a=[]
for a0 in xrange(t):
    n = int(raw_input().strip())
    a.append(n)
print growth(a)