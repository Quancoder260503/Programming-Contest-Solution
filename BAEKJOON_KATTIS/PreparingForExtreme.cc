#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 string line; 
 vector<int>read_time; 
 vector<string>topics;
 vector<vector<string>>g;  
 while(getline(cin, line)) { 
  stringstream ss(line);
  ss >> line; 
  read_time.push_back(stoi(line));
  vector<string>c;  
  while(ss >> line) { 
   topics.push_back(line); 
   c.push_back(line); 
  } 
  g.push_back(c); 
 }
 sort(topics.begin(), topics.end()); 
 topics.erase(unique(topics.begin(), topics.end()), topics.end()); 
 int N = sz(read_time), M = sz(topics); 
 vector<int>dp(1 << M, oo);
 dp[0] = 0;  
 for(int i = 0; i < N; i++) { 
  int maskG = 0; 
  for(auto v : g[i]) { 
   int pos = lower_bound(topics.begin(), topics.end(), v) - topics.begin(); 
   maskG |= (1 << pos); 
  }
  vector<int>ndp(dp.begin(), dp.end()); 
  for(int mask = 0; mask < (1 << M); mask++) { 
   ndp[mask | maskG] = min(ndp[mask | maskG], dp[mask] + read_time[i]); 
  }
  ndp.swap(dp); 
 }
 cout << dp[(1 << M) - 1] << '\n'; 
 return 0;
}