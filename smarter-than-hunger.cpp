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

int dist(pair<int, int>& a, pair<int, int>& b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int maximum(int a, int b){
	return (a > b) ? a : b;
}

int minimum(int a, int b){
	return (a < b) ? a : b;
}

int phi(int r1, int r2, int acc){
	int ans;
	state key = {maximum(r1, r2), minimum(r1, r2), acc};
	if(dp.count(key)){
		ans = dp[key];
	}else{
		if(r1 == k || r2 == k){
			ans = maximum(dist(butt[minimum(r1, r2)], butt[k]) - acc, 0);
		}else{
			int rn = maximum(r1, r2) + 1;
			int distf = dist(butt[r1], butt[rn]);
			int dists = dist(butt[r2], butt[rn]);
			int accf = 0, accs = 0;
			if(r1 != r2){
				if(rn == r1 + 1){
					dists = maximum(dists - acc, 0);
					accf = acc;
				}else{
					distf = maximum(distf - acc, 0);
					accs = acc;
				}
			}
			accf += distf;
			accs += dists;
			ans = phi(rn, r2, minimum(accf, w)) + distf;
			ans = minimum(ans, phi(r1, rn, minimum(accs, w)) + dists);
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