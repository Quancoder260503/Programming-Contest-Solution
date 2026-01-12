#include <bits/stdc++.h> 
#include <iostream>
 
using namespace std; 
 
#define sz(x) int(x.size())
 
vector<int> prefix_function(const vector<int>&s) {
  int n = s.size();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}
 
int kmp(const vector<int>&pattern, const vector<int>&text) {
  vector<int>cc(pattern.begin(), pattern.end());
  cc.push_back(128); 
  for(auto c : text) { cc.push_back(c); } 
  auto pi = prefix_function(cc);
  int ret = -1; 
  for (size_t i = sz(pi) - sz(text); i < sz(pi); ++i) {
   if(pi[i]) ret = max(ret, pi[i]); 
  }
  return ret;
}
 
int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M;
 vector<int>a(N), b(M); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 } 
 for(int i = 0; i < M; i++) { 
  cin >> b[i]; 
 } 
 cout << kmp(b, a) << '\n'; 
 return 0;
}
