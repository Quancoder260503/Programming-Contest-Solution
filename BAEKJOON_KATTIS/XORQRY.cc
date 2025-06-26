#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int block_size = 500;
const int maxf = (1 << 20);

int N, Q, K, a[maxf], b[maxf];
int64_t ret[maxf];

struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int sum(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c ^ bit[i];
    }
    return c;
  }
  int query(int L, int R) { 
   return sum(R) ^ sum(L - 1); 
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif ^ bit[i];
    }
  }
};
 

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> N >> Q;
 vector<int>a(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i]; 
 }
 vector<vector<pair<int, int>>>query(N + 1); 
 for(int i = 0, L, R; i < Q; i++) { 
  cin >> L >> R;
  query[R].push_back({L, i}); 
 }
 map<int, int>mp; 
 FT fenw(N + 2); 
 for(int i = 1; i <= N; i++) { 
  if(mp.count(a[i])) { 
   fenw.update(mp[a[i]], a[i]); 
  }
  mp[a[i]] = i; 
  fenw.update(mp[a[i]], a[i]); 
  for(auto [L, idx] : query[i]) { 
   ret[idx] = fenw.query(L, i); 
  }
 }
 for(int i = 0; i < Q; i++) { 
  cout << ret[i] << ' '; 
 }
 return 0; 
}

/* 
struct Query {
 int L, R, id;
 Query(int _L, int _R, int _id) : L(_L), R(_R), id(_id){};
 bool operator<(Query other) const {
  return make_pair(L / block_size, R) <
         make_pair(other.L / block_size, other.R);
 }
};

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> N >> Q;
 vector<Query> query;
 vector<int> a(N + 1), coord;
 for (int i = 1; i <= N; i++) {
  cin >> a[i];
  coord.push_back(a[i]); 
 }
 for (int i = 0, l, r; i < Q; i++) {
  cin >> l >> r;
  query.push_back(Query(l, r, i));
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 for(int i = 0; i <= N; i++) { 
  a[i] = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
 }
 int64_t acc = 0;
 sort(query.begin(), query.end());
 int cur_L = 1, cur_R = 0;
 for (auto cur_Q : query) {
  while (cur_R < cur_Q.R) {
   cur_R++;
   if (mp[a[cur_R]] == 0) {
    acc = acc ^ coord[a[cur_R]];
   }
   mp[a[cur_R]]++;
  }
  while (cur_L > cur_Q.L) {
   cur_L--;
   if (mp[a[cur_L]] == 0) {
    acc = acc ^ coord[a[cur_L]];
   }
   mp[a[cur_L]]++;
  }
  while (cur_R > cur_Q.R) {
   mp[a[cur_R]]--;
   if (mp[a[cur_R]] == 0) {
    acc = acc ^ coord[a[cur_R]];
   }
   cur_R--;
  }
  while (cur_L < cur_Q.L) {
   mp[a[cur_L]]--;
   if (mp[a[cur_L]] == 0) {
    acc = acc ^ coord[a[cur_L]];
   }
   cur_L++;
  }

  ret[cur_Q.id] = acc;
 }
 for (int i = 0; i < Q; i++) {
  cout << ret[i] << ' ';
 }
 return 0;
}
*/ 