#include "bits/stdc++.h"

using namespace std; 

struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int query(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
};

void solve() {
 int N;
 cin >> N;
 map<string, int> mp; 
 for (int i = 0; i < N; i++) {
  string s;
  cin >> s;
  mp[s] = i; 
 }
 FT fenw(N + 7);
 int ret = 0; 
 vector<int>a(N); 
 for (int i = 0; i < N; i++) {
  string s;
  cin >> s; 
  a[i] = mp[s]; 
 }
 for(int i = N - 1; i >= 0; i--) { 
  ret += fenw.query(a[i]); 
  fenw.update(a[i], 1); 
 }
 cout << ret << '\n'; 
 return; 
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int T;
 for (cin >> T; T--; ) {
  solve(); 
 }
 return 0;
}