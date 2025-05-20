#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
  while (b != 0) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll mulmod(ll a, ll b, ll mod) {
  ll result = 0;
  a %= mod;
  while (b > 0) {
    if (b & 1)
      result = (result + a) % mod;
    a = (a * 2) % mod;
    b >>= 1;
  }
  return result;
}

ll powmod(ll base, ll exp, ll mod) {
  ll result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1)
      result = mulmod(result, base, mod);
    base = mulmod(base, base, mod);
    exp >>= 1;
  }
  return result;
}

bool is_prime(ll n, int k = 5) {
  if (n < 2) return false;
  if (n == 2 || n == 3) return true;
  if (n % 2 == 0) return false;

  ll r = 0, d = n - 1;
  while (d % 2 == 0) {
    d /= 2;
    r++;
  }

  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  for (int i = 0; i < k; ++i) {
    ll a = rng() % (n - 3) + 2;
    ll x = powmod(a, d, n);
    if (x == 1 || x == n - 1)
      continue;
    bool composite = true;
    for (ll j = 0; j < r - 1; ++j) {
      x = powmod(x, 2, n);
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite)
      return false;
  }
  return true;
}

ll pollards_rho(ll n) {
  if (n % 2 == 0) return 2;
  if (is_prime(n)) return n;

  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  while (true) {
    ll c = rng() % n;
    auto f = [&](ll x) { return (mulmod(x, x, n) + c) % n; };
    ll x = 2, y = 2, d = 1;
    while (d == 1) {
      x = f(x);
      y = f(f(y));
      d = gcd(abs(x - y), n);
    }
    if (d != n)
      return d;
  }
}

void factor(ll n, vector<ll>& factors) {
  if (n == 1) return;
  if (is_prime(n)) {
    factors.push_back(n);
    return;
  }
  ll f = pollards_rho(n);
  factor(f, factors);
  factor(n / f, factors);
}

int main() {
  int T; cin >> T;
  while(T-- != 0){
    ll N; cin >> N;
    vector<ll> ans;
    factor(N, ans);
    sort(ans.begin(), ans.end());
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
