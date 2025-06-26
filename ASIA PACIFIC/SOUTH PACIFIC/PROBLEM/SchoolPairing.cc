#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int block_size = 700;
const int maxf = (1 << 22); 

map<int, int>counter; 
int N, Q, K, a[maxf];
int64_t ret[maxf];

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
  while (cin >> N >> Q >> K) {
    if(!N) break; 
    vector<Query> query;
    for (int i = 1, x; i <= N; i++) {
      cin >> a[i];
    }
    for (int i = 0, l, r; i < Q; i++) {
      cin >> l >> r;
      if(l > r) swap(l, r); 
      query.push_back(Query(l, r, i));
    }
    int64_t acc = 0;
    sort(query.begin(), query.end());
    int cur_L = 1, cur_R = 0;
    for (auto cur_Q : query) {
      while (cur_R > cur_Q.R) {
        counter[a[cur_R]]--;
        acc = acc - counter[K - a[cur_R]];
        cur_R--;
      }
      while (cur_L < cur_Q.L) {
        counter[a[cur_L]]--;
        acc = acc - counter[K - a[cur_L]];
        cur_L++;
      }
      while (cur_L > cur_Q.L) {
        cur_L--;
        acc = acc + counter[K - a[cur_L]];
        counter[a[cur_L]]++;
      }
      while (cur_R < cur_Q.R) {
        cur_R++;
        acc = acc + counter[K - a[cur_R]];
        counter[a[cur_R]]++;
      }
      ret[cur_Q.id] = acc;
    }
    for (int i = 0; i < Q; i++) {
      cout << ret[i] << '\n';
    }
    counter.clear(); 
    cout << '\n'; 
  }
  return 0;
}
/*
  The test case seems to be incorrect however the solution is acceptable.
*/