#!/bin/python

import sys

def pair(n,k,a):
    pairs = 0
    for i in range(len(a)):
        for j in range(i+1,len(a)):
            if (a[i]+a[j])%k == 0:
                pairs += 1
    return pairs
        

n,k = raw_input().strip().split(' ')
n,k = [int(n),int(k)]
a = map(int,raw_input().strip().split(' '))
print pair(n,k,a)