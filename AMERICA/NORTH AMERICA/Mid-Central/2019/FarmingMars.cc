#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size()) 

const int BLOCK = 300;

struct Query {
 int L, R, id;
 Query(int _L, int _R, int _id) : L(_L), R(_R), id(_id){};
 bool operator<(Query other) const {
  return make_pair(L / BLOCK, R) < make_pair(other.L / BLOCK, other.R);
 }
};

unordered_map<int, int>mp; 
multiset<int>ms; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int N, Q; 
 cin >> N >> Q;
 vector<Query> query;
 vector<int> a(N + 1); 
 for (int i = 1; i <= N; i++) {
  double x; 
  cin >> x; 
  a[i] = int(x * 1000000);
 // cout << a[i] << '\n'; 
 }
 for (int i = 0, l, r; i < Q; i++) {
  cin >> l >> r;
  query.push_back(Query(l, r, i));
 }
 sort(query.begin(), query.end());
 vector<int>ret(Q); 
 int cur_L = 1, cur_R = 0;
 for (auto cur_Q : query) {
  while (cur_R < cur_Q.R) {
   cur_R++;
   if(mp.count(a[cur_R])) { 
    int x = mp[a[cur_R]]; 
    auto it = ms.find(x); 
    if(it != ms.end()) { 
     ms.erase(it); 
    }
   }
   mp[a[cur_R]]++;
   ms.insert(mp[a[cur_R]]); 
  }
  while (cur_L > cur_Q.L) {
   cur_L--;
   if(mp.count(a[cur_L])) { 
    int x = mp[a[cur_L]]; 
    auto it = ms.find(x); 
    if(it != ms.end()) { 
     ms.erase(ms.find(x)); 
    }
   }
   mp[a[cur_L]]++;
   ms.insert(mp[a[cur_L]]); 
  }
  while (cur_R > cur_Q.R) {
   if(mp.count(a[cur_R])) { 
    int x = mp[a[cur_R]]; 
    auto it = ms.find(x); 
    if(it != ms.end()) { 
     ms.erase(it); 
    }
   }
   mp[a[cur_R]]--;
   if(mp[a[cur_R]] == 0) { 
    mp.erase(a[cur_R]); 
   }
   ms.insert(mp[a[cur_R]]); 
   cur_R--;
  }
  while (cur_L < cur_Q.L) {
   if(mp.count(a[cur_L])) { 
    int x = mp[a[cur_L]]; 
    auto it = ms.find(x); 
    if(it != ms.end()) { 
     ms.erase(it); 
    }
   }
   mp[a[cur_L]]--;
   if(mp[a[cur_L] == 0]) { 
    ms.erase(a[cur_L]); 
   }
   ms.insert(mp[a[cur_L]]); 
   cur_L++;
  }
  //cout << cur_Q.id << " " << cur_L << " " << cur_R << " " << ms.size() << '\n'; 
  ret[cur_Q.id] = (ms.size() && *prev(ms.end()) >= (cur_Q.R - cur_L + 1) / 2 + 1);
 }
 for (int i = 0; i < Q; i++) {
  cout << (ret[i] ? "" : "un") << "usable\n";
 }
 return 0;
}
