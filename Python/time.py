# you can write to stdout for debugging purposes, e.g.
# print "this is a debug message"

def solution(A, B, C, D):
    # write your code in Python 2.7
    digits = [A,B,C,D]
    digits.sort()
    reverse = digits[::-1]
    result = []
    flag1 = 0
    flag3 = 0
    for i in range(0,len(reverse)):
        if reverse[i]<=2:
            flag1 = 1
            result.insert(0,reverse[i])
            reverse.remove(reverse[i])
            break
    
    if flag1 == 0:
        return "NOT POSSIBLE"
    
    for i in range(0,len(reverse)):
        if result[0]==2:
            if reverse[i]<=3:
                result.insert(1,reverse[i])
                reverse.remove(reverse[i])
                break
        else:
            if reverse[i]<=9:
                result.insert(1,reverse[i])
                reverse.remove(reverse[i])
                break
        
    for i in range(0,len(reverse)):
        if reverse[i]<=5:
            flag3 =1
            result.insert(2,reverse[i])
            reverse.remove(reverse[i])
            break

    if flag3 == 0:
        return ("NOT POSSIBLE")

    for i in range(0,len(reverse)):
        if reverse[i]<=9:
            result.insert(3,reverse[i])
            reverse.remove(reverse[i])
            break
    
    time = str(result[0])+str(result[1])+":"+str(result[2])+str(result[3])
    return time
