#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int MOD = 998244353;

const int oo = 1e9 + 2; 
 
const int LOG = 20;

int64_t dp[250][250][250], cache[250][250][250]; 
 
class RedBlackBall { 
 public :
  void solve() { 
   int N, M; 
   cin >> N >> M; 
   vector<int64_t>ifact(10002), fact(10002); 
   fact[0] = ifact[0] = 1; 
   for(int i = 1; i < sz(fact); i++) { 
    fact[i] = fact[i - 1] % MOD * i % MOD; 
    ifact[i] = mod_inv(fact[i], MOD); 
   }
   auto Comb = [&](int n, int k) { 
    if(n < k || k < 0) return 0LL; 
    return fact[n] % MOD * ifact[k] % MOD * ifact[n - k] % MOD; 
   }; 
   vector<pair<int, int>>a(N + 1); 
   vector<int>coord{-1, oo}; 
   int og_black = 0, og_red = 0; 
   for(int i = 1; i <= N; i++) {
    string c; 
    cin >> a[i].first >> c; 
    og_red   += (c == "RED"); 
    og_black += (c == "BLACK"); 
    a[i].second = (c == "RED"); 
    coord.push_back(a[i].first); 
   } 
   sort(a.begin() + 1, a.end()); 
   a[0]     = {-1,   a[1].second}; 
   a.push_back({oo,  a[N].second});  
   for(int i = 0, x; i < M; i++) { 
    cin >> x; 
    coord.push_back(x); 
   }
   sort(coord.begin(), coord.end()); 
   coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
   int m = sz(coord); 
   
   memset(cache, -1, sizeof(cache)); 
   dp[0][0][0] = 1; 
   for(int ptr = 0; ptr <= N; ptr++) { 
    int pos_L = lower_bound(coord.begin(), coord.end(), a[ptr].first)     - coord.begin(); 
    int pos_R = lower_bound(coord.begin(), coord.end(), a[ptr + 1].first) - coord.begin(); 
    if(a[ptr].second == a[ptr + 1].second) {
      int num_balls = pos_R - pos_L - 1; 
      for(int red = 0; red <= M; red++) { 
       for(int black = 0; black <= M - red; black++) {
        if(red + num_balls <= M && a[ptr].second) { 
         (dp[ptr + 1][red + num_balls][black] += dp[ptr][red][black] % MOD * fact[num_balls] % MOD * 
                                                 Comb(black + red + num_balls, num_balls) % MOD) %= MOD; 
        }
        if(black + num_balls <= M && !a[ptr].second) { 
         (dp[ptr + 1][red][black + num_balls] += dp[ptr][red][black] % MOD * fact[num_balls] % MOD * 
                                                 Comb(black + red + num_balls, num_balls) % MOD) %= MOD; 
        }
       }
      }
    } else {
    // f[i][j][k] = {number of ways to place uncolored into [a[i], a[j]) such that there are k red balls}
     function<int64_t(int, int, int)> memo = [&](int i, int j, int num_red) -> int64_t { 
      if(i + 1 == j) return num_red == 0; 
      int64_t &ret = cache[i][j][num_red]; 
      if(ret != -1) return ret; 
      ret = 0; 
      for(int k = i + 1; k < j; k++) { 
       int dist_a = coord[k] - coord[i]; 
       int dist_b = coord[j] - coord[k]; 
       if(dist_a <= dist_b) { 
        ret += fact[k - i - 1] % MOD * Comb(j - i - 2, k - i - 1) % MOD * memo(k, j, num_red - (k - i) * a[ptr].second) % MOD;
        ret %= MOD;  
       } else { 
        ret += fact[j - k - 1] % MOD * Comb(j - i - 2, j - k - 1) % MOD * memo(i, k, num_red - (j - k) * a[ptr + 1].second) % MOD; 
        ret %= MOD; 
       } 
      }
      return ret; 
     }; 
     int num_balls = pos_R - pos_L - 1;
     for(int num_red = 0; num_red <= num_balls; num_red++) { 
      memo(pos_L, pos_R, num_red); 
     }
     for(int red = 0; red <= M; red++) { 
      for(int black = 0; black <= M - red; black++) { 
       for(int new_red = 0; new_red <= num_balls; new_red++) { 
        int new_black = num_balls - new_red; 
        if(red + new_red <= M && black + new_black <= M) { 
          (dp[ptr + 1][red + new_red][black + new_black] += dp[ptr][red][black] % MOD * 
                                                            memo(pos_L, pos_R, new_red) % MOD *
                                                            Comb(black + red + num_balls, num_balls) % MOD) %= MOD; 
        }
       }
      }
    } 
   } 
  }
  int64_t ans = 0; 
  for(int red = og_red; red <= N + M; red++) {
   int black = N + M - red; 
   if(black >= og_black && red > black) {
    (ans += dp[N + 1][red - og_red][black - og_black]) %= MOD; 
   }
  }
  cout << ans << '\n'; 
  return;  
 } 
 private : 
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
}; 
 
int main(void) { 
  RedBlackBall task; 
  task.solve(); 
  return 0; 
}