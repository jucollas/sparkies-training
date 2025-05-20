

data = [
	(0, 10, 0), 
	(10, 0, 1), 
	(12, 8, 1), 
	(5, 5, 0), 
	(11, 2, 1), 
	(11, 3, 0)
]

def minOne(A):
	ans = 0
	while ans < len(A) and A[ans][1] == 0:
		ans += 1
	return ans

def maxOne(A):
	ans = len(A) - 1
	while ans >= 0 and A[ans][1] == 0:
		ans -= 1
	return ans

def V(s, t):
	A = list()
	for ai, bi, ci in data:
		A.append((ai * s + bi * t, ci))
	A.sort()
	print(A)
	return maxOne(A) - minOne(A)

def main():
	R = [ i * 0.01 for i in range(100)]
	for step in R:
		s, t = step, 1 - step
		vi = V(s, t)
		print("s : %f, t : %f, vi : %d" %(s, t, vi))


main()