# Enter your code here. Read input from STDIN. Print output to STDOUT
import math
n = int(raw_input())

def adv(n):
    res = 0
    m = 5
    for i in range(0,n):
        m = math.floor(m/2)
        res += m
        m = m*3
    return int(res)        
print adv(n)