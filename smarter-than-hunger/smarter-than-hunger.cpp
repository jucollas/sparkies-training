#include <bits/stdc++.h>
using namespace std;

using state = tuple<int, int, int>;

struct StateHash {
  size_t operator()(const state& s) const {
  	int  r1 = get<0>(s);
  	int  r2 = get<1>(s);
  	int  acc = get<2>(s);
    return r1 | (r2 << 8) | (acc << 16);
  }
};

int k, w;
vector<pair<int, int>> butt;
unordered_map<state, int, StateHash> dp;

int d(pair<int, int>& a, pair<int, int>& b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int phi(int u, int v, int r){
	int ans;
	state key = {u, v, r};
	if (dp.count(key)){
		ans = dp[key];
	}else{
		if (u == k){
			ans = max(d(butt[v], butt[k]) - r, 0);
		}else{
			int s = u + 1;
			int du = d(butt[u], butt[s]);
			int dv = max(d(butt[v], butt[s]) - r, 0);
			int ru = min(du + r, w), rv = dv;
			ans = min(phi(s, v, ru) + du, phi(s, u, rv) + dv);
		}
		dp[key] = ans;
	}
 return ans;
}

int main(){
	int n, m;
	while(cin >> n >> m){
		cin >> k;
		w = n + m;
		butt = {{1, 1}};
		for(int i = 0; i < k; ++i){
			int r, c; cin >> r >> c;
			butt.push_back({r, c});
		}
		butt.push_back({n, m});

		k = butt.size() - 1;
		dp = {};

		int ans = phi(0, 0, 0) + 1;
		cout << ans << endl;
	}
	return 0;
}