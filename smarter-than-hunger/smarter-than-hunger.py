"""
Author: Juan Diego Collazos Mejia
Date: 23/05/2025
url: https://onlinejudge.org/external/131/13179.pdf

Accepted version of the solution to the "Smarter than Hunger" problem.
Uses dynamic programming strategy.


d: (N x N) x (N x N) -> N : Manhattan distance

Let u, v, r ∈ ℕ and butt[0..N).

phi(u, v, r) = {
  max(d(butt[v], butt[N]) - r, 0)   if u == N
  min(
    phi(u + 1, v, du + r) + du,
    phi(u + 1, u, dv) + dv
  )                                 otherwise
  where:
    du = d(butt[u], butt[s])
    dv = max(d(butt[v], butt[s]) - r, 0)
}
"""
from sys import stdin

butt = list()
dp = dict()
k, w = 0, 0

def d(a, b):
  return abs(a[0] - b[0]) + abs(a[1] - b[1])

def phi(u, v, r):
  key = (u, v, r)
  if key in dp:
    ans = dp[key]
  else:
    if u == k:
      ans = max(d(butt[v], butt[k]) - r, 0)
    else:
      s = u + 1
      du = d(butt[u], butt[s])
      dv = max(d(butt[v], butt[s]) - r, 0)
      ru = min(du + r, w)
      ans = min(phi(s, v, ru) + du, phi(s, u, dv) + dv)
    dp[key] = ans
  return ans

def main():
  global butt, dp, k, w
  line = stdin.readline()
  while line != '':
    n, m = map(int, line.split())
    k = int(stdin.readline().strip())
    w = n + m
    butt = [(1, 1)]
    for _ in range(k):
      r, c = map(int, stdin.readline().split())
      butt.append((r, c))
    butt.append((n, m))

    k = len(butt) - 1
    dp = dict()

    ans = phi(0, 0, 0) + 1
    print(ans)

    line = stdin.readline()

main()