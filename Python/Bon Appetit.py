# Enter your code here. Read input from STDIN. Print output to STDOUT
n,k = map(int,raw_input().split())
c = map(int,raw_input().split())
b = int(raw_input())

def extra(n,k,c,b):
    total = 0
    c.pop(k)
    for i in c:
        total += i
    actual = total/2
    
    if b == actual:
        return "Bon Appetit"
    else:
        return b - actual
print extra(n,k,c,b)    