#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ll long long 

const int oo = 1e8; 
// Not so good algorithm 
// 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   int n; 
   cin >> n; 
   vector<int>a(n);
   int total = 0; 
   for(auto &x : a) cin >> x;
   vector<int>l(n + 1, oo);
   for(int i = 0; i < n; i++) { 
    l[a[i]] = i; 
   }  
   for(int i = 0; i <= n; i++) { 
    total += (l[i] < oo); 
   }
   cout << total << '\n'; 
   priority_queue<int, vector<int>, greater<int>>ls(l.begin(), l.end());
   using P = array<int, 2>; 
   priority_queue<P, vector<P>, greater<P>>mx_cand, mn_cand; 
   for(int i = 0; i <= ls.top(); i++) { 
    mx_cand.push({-a[i], i});
    mn_cand.push({a[i],  i}); 
   } 
   vector<int>vis(n + 1), ret; 
   int curr_pos; 
   while(sz(mn_cand)) { 
    auto [x, pos] = (sz(ret) % 2 == 0 ? mx_cand.top() : mn_cand.top());
    if(sz(ret) % 2 == 0) { 
      x = x * -1;   
      mx_cand.pop(); 
    } else { 
      mn_cand.pop(); 
    }
    ret.push_back(x); 
    vis[x] = 1; 
    curr_pos = pos + 1;
    while(ls.top() < oo && vis[a[ls.top()]]) {
     auto latest_pos = ls.top(); 
     ls.pop(); 
     for(int j = latest_pos; j <= min(n - 1, ls.top()); j++) { 
      mx_cand.push({-a[j], j}); 
      mn_cand.push({a[j], j}); 
     }
    }
    while(mn_cand.size() && ((mn_cand.top()[1] < curr_pos) || vis[mn_cand.top()[0]]))  mn_cand.pop(); 
    while(mx_cand.size() && ((mx_cand.top()[1] < curr_pos) || vis[-mx_cand.top()[0]])) mx_cand.pop(); 
   }
   for(auto &x : ret) cout << x << " "; 
   cout << '\n'; 
  }
  return 0;
}