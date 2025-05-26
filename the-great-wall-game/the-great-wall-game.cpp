/*
Accepted solution to the problem 'The Great Wall Game'.
Uses the Hungarian algorithm for matching.

Author: Juan Diego Collazos
Date: 26/05/2025
URL: https://onlinejudge.org/external/10/1045.pdf
*/

#include <bits/stdc++.h>

using namespace std;
int INF = INT_MAX;
int MAX = 15;

int hungarian(vector<vector<int>>& G){
	int n = G.size();
	vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
	for (int i = 1; i <= n; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<int> minv(n + 1, INF);
		vector<bool> used(n + 1, false);

		int tmp = -1;
		while (tmp != 0){
			used[j0] = true;
			int i0 = p[j0], j1 = 0;
			int delta = INF;

			for (int j = 1; j <= n; ++j) {
				if (!used[j]) {
					int cur = G[i0 - 1][j - 1] - u[i0] - v[j];
					if (cur < minv[j]) {
						minv[j] = cur;
						way[j] = j0;
					}
					if (minv[j] < delta) {
						delta = minv[j];
						j1 = j;
					}
				}
			}

			for (int j = 0; j <= n; ++j) {
				if (used[j]) {
					u[p[j]] += delta;
					v[j] -= delta;
				}else {
					minv[j] -= delta;
				}
			}
			j0 = j1;
			tmp = p[j0];
		}
		tmp = -1;
		while(tmp != 0){
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
			tmp = j0;
		}
	}
	int ans = 0;
	for (int j = 1; j <= n; ++j) {
		int i = p[j];
		ans += G[i - 1][j - 1];
	}
	return ans;
}

int dist(pair<int, int> a, pair<int, int> b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<vector<pair<int, int>>> makeLines(int n){
	vector<vector<pair<int, int>>> ans((n + 1) << 1);
	int k = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			ans[k].push_back({i, j});
			ans[k + n].push_back({j, i});
		}
		++k;
	}
	k = n << 1;
	for(int i = 0; i < n; ++i){
		ans[k].push_back({i, i});
		ans[k + 1].push_back({n - i - 1, i});
	}
	return ans;
}

int main(){
	int n; cin >> n;
	int n_case = 1;
	while(n != 0){
		vector<vector<int>> G(n, vector<int>(n));
		vector<vector<pair<int, int>>> lines = makeLines(n);
		vector<pair<int, int>> stones;
		for(int i = 0; i < n; ++i){
			int x, y; cin >> x >> y;
			stones.push_back({x - 1, y - 1});
		}

		int ans = INF, l = lines.size();
		for(int k = 0; k < l; ++k){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					G[i][j] = dist(stones[i], lines[k][j]);
				}
			}
			ans = min(ans, hungarian(G));
		}
		printf("Board %d: %d moves required.\n\n", n_case++, ans);
		cin >> n;
	}
	return 0;
}