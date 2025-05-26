/*
In-process version of the solution to the 'Jaguar king' problem

Autor: Juan Diego Collazos Mejia
Date: 26/05/2025
Url: https://onlinejudge.org/external/111/11163.pdf
*/

#include<bits/stdc++.h>
using namespace std;

int INF = 1 << 29;
vector<vector<int>> jumps = {
	{-3, -1, 4, -4},
	{ 1,  3, 4, -4},
	{ 1, -1, 4, -4},
	{ 1, -1, 4, -4}
};

int ans;
int N;
vector<int> A;

bool check(vector<int>& v){
	bool res = true;
	int i = 1;
	while(i <= N && res){
		res = v[i] == A[i];
		++i;
	}
	//cout << res << endl;
	return res;
}

void printVector(vector<int> v){
	for(int i = 0; i < (int)v.size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;
}

void backtrack(int i, int k, vector<int>& v){
	if(check(v)){
		ans = min(ans, k);
	}else if(ans > k){
		int mod = i % 4;
		for(int index = 0; index < 4; ++index){
			int j = i + jumps[mod][index];
			if(0 < j && j <= N){
				swap(v[i], v[j]);
				backtrack(j, k + 1, v);
				swap(v[i], v[j]);
			}
		}
	}
}

int main(){
	int n_case = 1;
	N; cin >> N;
	while (N != 0){
		A = {0};
		for(int i = 0; i < N; ++i){
			int tmp; cin >> tmp;
			A.push_back(tmp);
		}
		ans = INF;
		vector<int> v(N + 1);
		for(int i = 0; i <= N; ++i)
			v[i] = i;

		backtrack(1, 0, v);

		cout << "Set " << n_case++ << ":" << endl;
		cout << ans << endl;
		cin >> N;
	}
	return 0;
}


