x=raw_input("Choose an integer: ")

def reverse(x):
	result = ''
	string = str(x)
	n= len(string)-1
	for i in range(len(string)):
		result += string[n]
		n=n-1
	return result

print reverse(x)
