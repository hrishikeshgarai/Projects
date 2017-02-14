def deleteFromCircle(n,m,k):
	aList = []
	for i in range(1,n):
		aList.append(i)
	aList.append(0)
	
	newList = aList[::-1]
	i=0
	while (len(newList) > k):
		newList.pop(i+m-1)
		i+=m-1
		if len(newList) == 0:
			newList = []
		else:
			while i+m-1 >= len(newList):
				i=i-len(newList)
	newList.sort()
	return newList


n,m,k = map(int,raw_input().split())

print deleteFromCircle(n,m,k)
	
"""

		newList = newList[m:]+newList[:m-1]

"""
