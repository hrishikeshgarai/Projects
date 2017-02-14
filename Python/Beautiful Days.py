# Enter your code here. Read input from STDIN. Print output to STDOUT
i,j,k = map(int,raw_input().split())

def day(i,j,k):
    bd=0
    for a in range(i,j+1):
        b = str(a)
        c = b[::-1]
        if abs(int(c)-a)%k == 0:
            bd += 1
    return bd
print day(i,j,k)