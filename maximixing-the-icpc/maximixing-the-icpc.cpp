#include<bits/stdc++.h>
using namespace std;
int INF = 1 << 30;
vector<vector<int>> G(65,vector<int>(65, 0));
int k = 0;

vector<int> blossom(vector<list<int>>& graph) {
  int n = graph.size(), timer = -1;
  vector<int> mate(n, -1), label(n), parent(n), 
              orig(n), aux(n, -1), q;
  auto lca = [&](int x, int y) {
    for (timer++; ; swap(x, y)) {
      if (x == -1) continue;
      if (aux[x] == timer) return x;
      aux[x] = timer;
      x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
    }
  };
  auto blossom = [&](int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w; w = mate[v];
      if (label[w] == 1) label[w] = 0, q.push_back(w);
      orig[v] = orig[w] = a; v = parent[w];
    }
  };
  auto augment = [&](int v) {
    while (v != -1) {
      int pv = parent[v], nv = mate[pv];
      mate[v] = pv; mate[pv] = v; v = nv;
    }
  };
  auto bfs = [&](int root) {
    fill(label.begin(), label.end(), -1);
    iota(orig.begin(), orig.end(), 0);
    q.clear(); 
    label[root] = 0; q.push_back(root);
    for (int i = 0; i < (int)q.size(); ++i) {
      int v = q[i];
      for (auto x : graph[v]) {
        if (label[x] == -1) {
          label[x] = 1; parent[x] = v;
          if (mate[x] == -1) 
            return augment(x), 1;
          label[mate[x]] = 0; q.push_back(mate[x]);
        } else if (label[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a); blossom(v, x, a);
        }
      }
    }
    return 0;
  };
  // Time halves if you start with (any) maximal matching.
  for (int i = 0; i < n; i++) 
    if (mate[i] == -1) 
      bfs(i);
  return mate;
}


bool check(int v){
  vector<list<int>> graph(k + 1);
  for(int i = 1; i <= k; ++i){
    for(int j = 1; j <= k - i; ++j){
      if(G[i][i + j] >= v){
        graph[i].push_back(i + j);
        graph[i + j].push_back(i);
      }
    }
  }
  vector<int> mate = blossom(graph);
  bool ans = true;
  int i = 1, n = mate.size();
  while(i < n && ans) {
    ans = ans & mate[i] != -1;
    i++;
  }
  return ans;
}

int binarySearch(int a, int b){
  int low = a, hi = b;
  int ans = -1;
  while (low <= hi) {
    int mid = low + ((hi - low) >> 1);
    if (check(mid)){
      low = mid + 1;
      ans = mid;
    }else{
      hi = mid - 1;
    }
  }
  return ans;
}

int main(){
  int T; cin >> T;
  int n_case = 0; 
  while (n_case++ < T){
    int N; cin >> N;
    k = (1 << N);
    int maxi = -1, mini = INF;
    for(int i = 1; i <= k; ++i){
      for(int j = 1; j <= k - i; ++j){
        int icpc; cin >> icpc;
        G[i][i + j] = icpc;
        mini = min(mini, icpc);
        maxi = max(maxi, icpc);
      }
    }
    int ans = binarySearch(mini, maxi);
    cout << "Case " << n_case << ": " << ans << endl;
  }
  return 0;
}




