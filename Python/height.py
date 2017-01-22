# you can write to stdout for debugging purposes, e.g.
# print "this is a debug message"
def solution(A):
    # write your code in Python 2.7
    B = list(A)
    B.sort()
    start_index = 0
    end_index = 0
    for i in range(0,len(A)):
        if B[i] != A[i]:
            start_index = i
            break
    for i in range(len(A)-1,-1,-1):
        if B[i] != A[i]:
            end_index = i
            break
    
    result = (end_index - start_index + 1)
    return result