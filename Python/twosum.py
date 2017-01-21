series = raw_input("Enter a list of integers: ").split(" ")
target = raw_input("Enter the two sum target: ")

def twosum(series, target):
	new_list = []
	for i in series:
		for j in series:
			if int(i)+int(j)==int(target):
				new_list.append(series.index(i))
				new_list.append(series.index(j))
				break
		if new_list!=[]:
			break
	return new_list

print twosum(series, target)	
