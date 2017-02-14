#!/bin/python

import sys

def prof(y,z,t):
    res = ""
    for i in range(t):
        students = 0        
        x = z[i]
        for j in x:
            if j <= 0:
                students += 1
        if students >= y[i]:
            res = res + "NO" + "\n"
        else:
            res = res + "YES" + "\n" 
    return res    

t = int(raw_input().strip())
y = []
z = []
for a0 in xrange(t):
    n,k = raw_input().strip().split(' ')
    n,k = [int(n),int(k)]
    a = map(int,raw_input().strip().split(' '))
    y.append(k)
    z.append(a)
print prof(y,z,t)