#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1e6 + 2; 

vector<int> prefix_function(vector<int> &s) {
  int n = sz(s); 
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0);
  cout.tie(0); 
  int N;
  cin >> N;
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  cout << N - prefix_function(a).back() << '\n'; 
  return 0; 
} 