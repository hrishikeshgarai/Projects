def solution(A):
	N = len(A)
	B = []
	for i in range(0,N):
		lhs = 0
		rhs = 0
		for j in range(0,i):
			lhs += A[j]
		for k in range(i+1,N):
			rhs += A[k]
		if lhs==rhs:
			B.append(i)
	return B
A = [-1,3,-4,5,1,-6,2,1]
#solution(A)
print solution(A)
