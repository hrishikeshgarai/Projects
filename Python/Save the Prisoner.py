# Enter your code here. Read input from STDIN. Print output to STDOUT
t = int(raw_input())
x = []
y = []
z = []
for i in range(t):
    n,m,k = map(int,raw_input().split())
    x.append(n)
    y.append(m)
    z.append(k)
    
def poison(x,y,z,t):
    res = ""
    for i in range(t):
        a = ((y[i]+z[i])%x[i])-1
        if a <= 0:
            a = x[i]+a
        res = res + str(a) + "\n"
    return res

print poison(x,y,z,t)