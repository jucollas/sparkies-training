/*
Unaccepted version of the solution to the Factoring Large Integers problem
Use the Whell factoring technique with a mod 30 wheel.

Author: Juan Diego Collazos
Date : 19/5/2025
Problem : https://onlinejudge.org/external/114/11476.pdf

Reference:
Wheel factorization: https://cp-algorithms.com/algebra/factorization.html
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> trial_division(ll n) {
	vector<ll> factorization;
	for (int d : {2, 3, 5}) {
		while (n % d == 0) {
			factorization.push_back(d);
			n /= d;
		}
	}
	static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
	int i = 0;
	for (ll d = 7; d * d <= n; d += increments[i++]) {
		while (n % d == 0) {
			factorization.push_back(d);
			n /= d;
		}
		if (i == 8)
			i = 0;
	}
	if (n > 1)
		factorization.push_back(n);
	return factorization;
}


int main(){
  int T; cin >> T;
  while(T-- != 0){
    ll N; cin >> N;
    vector<ll> ans = trial_division(N);
    cout << N << " =";
    int act  = 0, n = ans.size();
    while(act < n){
      int i = act, cnt = 0;
      while(i < n && ans[act] == ans[i]){
        cnt += 1;
        i++;
      }
      cout << " " << ans[act];
      if(cnt > 1) cout << "^" << cnt;
      if(i != n) cout << " *";
      act = i;
    }
    cout << endl;
  }
  return 0;
}