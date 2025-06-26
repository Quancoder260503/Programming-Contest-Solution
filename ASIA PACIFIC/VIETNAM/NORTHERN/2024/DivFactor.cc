#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int block_size = 500;
const int maxf = 1e5 + 10; 

struct Query {
  int L, R, id;
  Query(int _L, int _R, int _id) : L(_L), R(_R), id(_id){};
  bool operator < (Query other) const {
    return make_pair(L / block_size, R) <
           make_pair(other.L / block_size, other.R);
  }
};


int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

int64_t c[maxf], ret[maxf], counter[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int MOD;
  string S;  
  cin >> MOD >> S; 
  int N = sz(S); 
  if(MOD == 2 || MOD == 5) { 
    vector<int64_t>num(N), acc(N); 
    for(int i = 0; i < N; i++) { 
     num[i] = ((S[i] - '0') % MOD == 0) + (i ? num[i - 1] : 0); 
     acc[i] = ((S[i] - '0') % MOD == 0) * (i + 1) + (i ? acc[i - 1] : 0); 
    }
    int Q;
    cin >> Q;  
    for(int i = 0, L, R; i < Q; i++) { 
     cin >> L >> R;
     --L, --R; 
     int64_t ret = ((acc[R] - (L ? acc[L - 1] : 0)) - (num[R] - (L ? num[L - 1] : 0)) * L);
     cout << ret << '\n'; 
    }
    return 0; 
  }
  //cout << MOD << '\n'; 
  int64_t inv10 = mod_inv(10, MOD); 
  int64_t sum = 0, ipw = 1; 
  vector<int64_t>coord{0};
  for(int i = 0; i < N; i++) { 
   sum = (sum * 10 % MOD + (S[i] - '0')) % MOD;  
   ipw = ipw % MOD * inv10 % MOD; 
   c[i + 1] = sum % MOD * ipw % MOD;
   coord.push_back(c[i + 1]); 
  }
  int Q; 
  cin >> Q; 
  vector<Query>query; 
  for(int i = 0, L, R; i < Q; i++) { 
   cin >> L >> R; 
   query.push_back(Query(L - 1, R, i)); 
  }
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
  for(int i = 1; i <= N; i++) { 
    c[i] = lower_bound(coord.begin(), coord.end(), c[i]) - coord.begin(); 
  }
  sort(query.begin(), query.end());
  int cur_L = 1, cur_R = 0; 
  int64_t acc = 0;
  for(auto cur_Q : query) {
    while (cur_R > cur_Q.R) {
     counter[c[cur_R]]--;
     acc -= counter[c[cur_R]];
     cur_R--;
    }
    while (cur_L < cur_Q.L) {
     counter[c[cur_L]]--;
     acc -= counter[c[cur_L]];
     cur_L++;
    }
    while (cur_L > cur_Q.L) {
     cur_L--;
     acc += counter[c[cur_L]];  
     counter[c[cur_L]]++;
    }
    while (cur_R < cur_Q.R) {
     cur_R++;
     acc += counter[c[cur_R]];
     counter[c[cur_R]]++;
    }
    ret[cur_Q.id] = acc;
  }
  for(int i = 0; i < Q; i++) { 
    cout << ret[i] << '\n'; 
  }
  return 0; 
  return 0; 
}
