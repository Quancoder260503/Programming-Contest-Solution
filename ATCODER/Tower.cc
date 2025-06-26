#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int maxf = 2e5 + 10; 

int main(void) { 
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>w(N + 1), s(N + 1), v(N + 1); 
  vector<int64_t>dyn(maxf); 
  int opt = 0; 
  for(int i = 1; i <= N; i++) { 
    cin >> w[i] >> s[i] >> v[i]; 
    opt = max(opt, s[i] + w[i]); 
  } 
  vector<int>ord(N); 
  iota(ord.begin(), ord.end(), 1); 
  sort(ord.begin(), ord.end(), [&](int i, int j) { 
    return w[i] + s[i] < w[j] + s[j]; 
  });
  for(int pos = 0; pos < N; pos++) {
    int i = ord[pos]; 
    for(int j = s[i] + w[i]; j >= w[i]; j--) { 
      dyn[j] = max(dyn[j], dyn[j - w[i]] + v[i]); 
    }
  }
  cout << *max_element(dyn.begin(), dyn.end()) << '\n'; 
  return 0; 
}

