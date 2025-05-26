#include <bits/stdc++.h>

using namespace std;
int INF = INT_MAX;

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