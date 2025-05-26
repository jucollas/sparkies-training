"""
In-process version of the solution to the 'Horse shoe scoring' problem

Author: Juan Diego Collazos
Date : 20/5/2025
Problem : https://onlinejudge.org/external/5/569.pdf
"""


from sys import stdin


def within(center, A):
	xc, yc = center
	xa, ya = A 

	vx, vy = xa - xc, ya - yc
	ux, uy = -xc, -yc

	dist_square = xc**2 + yc**2
	if dist_square > 81:
		ans = False
	else:
		dot = vx * ux + vy * uy
		ans = dot > 0
	return ans

def pivoted(A):
	ax, ay = A
	dist_square = ax**2 + ay**2
	ans = True
	if dist_square > 229.28427124746193:
		ans = False
	return ans

def toucher(center):
	xc, yc = center
	dist_square = xc**2 + yc**2
	ans = False
	if dist_square == 81:
		ans = True
	return ans

def point(center, A):
	ans = 0
	if within(center, A):
		if toucher(center):
			ans = 2
		else:
			ans = 5
	elif pivoted(A):
		ans = 1
	return ans

def main():
	line = stdin.readline()
	print("Turn Score")
	turn = 1
	while line != '':
		score = 0
		for i in range(4):
			center_x, center_y, A_x, A_y = map(float, line.split())
			score += point((center_x, center_x), (A_x, A_y))
			line = stdin.readline()
		print("%4d %4d" %(turn, score))




main()

