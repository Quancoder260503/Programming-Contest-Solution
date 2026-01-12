#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

const int maxn = 1e6 + 10; 
const int oo = 1e9 + 10; 

set<pair<int, int>>ms[maxn];
int n, m;

void update(int id, int val, int pos) {
 for(pos++; pos < maxn; pos += pos & (-pos)) {
  if(id < 0) {
   ms[pos].erase({val, -id});
  } else {
   ms[pos].insert({val, id});
  }
 }
 return;
}

pair<int, int>query(int pos, int lbound) {
 pair<int, int>ret = {oo, oo};
 for(pos++; pos > 0; pos -= pos & (-pos)) {
  auto it = ms[pos].lower_bound({lbound, -1});
  if(it != ms[pos].end()) ret = min(ret, *it);
 }
 return ret;
}

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0); 
 cin >> n;
 vector<int>coord, l(n + 1), r(n + 1);
 for(int i = 1; i <= n; i++) { 
  cin >> l[i] >> r[i];
  coord.push_back(l[i]);
  coord.push_back(r[i]);  
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 m = coord.size(); 
 pair<pair<int, int>, int>st = {{oo, oo}, -1};  
 for(int i = 1; i <= n; i++) {
  l[i] = lower_bound(coord.begin(), coord.end(), l[i]) - coord.begin() + 1;
  r[i] = lower_bound(coord.begin(), coord.end(), r[i]) - coord.begin() + 1; 
  update(i, r[i], l[i]);  
  if(r[i] < st.first.second) { 
   st = {{l[i], r[i]}, i}; 
  } else if(r[i] == st.first.second && l[i] > st.first.first) { 
   st = {{l[i], r[i]}, i}; 
  }
 } 
 vector<int>ret{st.second}; 
 int curr = ret.back(); 
 //cout << curr << '\n'; 
 for(int i = 1; i < n; i++) {
  update(-curr, r[curr], l[curr]);
  auto nxt = query(r[curr], l[curr]);
  if(nxt.first == oo) { 
    cout << "NO\n";
    exit(0);
  } 
  ret.push_back(nxt.second); 
  curr = ret.back();
 }
 cout << "YES\n";
 for(auto &x : ret) cout << x << " "; 
 cout << '\n';
 return 0; 
}
/** Not fully tested since the server is not capable of doing so */