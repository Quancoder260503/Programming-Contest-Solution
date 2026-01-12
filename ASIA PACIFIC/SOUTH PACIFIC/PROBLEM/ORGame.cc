#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

using namespace std; 

#define int64_t long long

const int LOG = 31;  
const int maxn = 5e5 + 10; 
const int64_t oo = 1e14; 

int N, K; 
int64_t dp[maxn], prefix[maxn], sparse[maxn][LOG], sdp[maxn][LOG], v[maxn]; 
/*
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
*/ 

int64_t get(int a, int b) { 
  if(a == b) return sparse[a][0]; 
  int dep = LOG - __builtin_clz(b - a);
  //cerr << dep << " " << a << " " << b << '\n'; 
  return sparse[a][dep] | sparse[b - (1 << dep) + 1][dep]; 
 }

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> K; 
  for(int i = 1; i <= N; i++) { 
    cin >> sparse[i][0]; 
    prefix[i] = prefix[i - 1] + sparse[i][0]; 
  }
  for(int i = 1; i < LOG; i++) { 
   for(int j = 1; j + (1 << (i - 1)) <= N; j++) { 
    sparse[j][i] = sparse[j][i - 1] | sparse[j + (1 << (i - 1))][i - 1]; 
   }
  }
  memset(sdp, 63, sizeof sdp); 
  memset(dp, 63, sizeof dp);
  {
   /*
   int m = (N - 1) % (K - 1) + 1; 
   vector<vector<int64_t>>dyn(N + 1, vector<int64_t>(m + 1, oo)); 
   dyn[0][0] = 0; 
   for(int i = 1; i <= N; i++) { 
    for(int j = 0; j < i; j++) {
     for(int k = 1; k <= m; k++) { 
       if(i - j == K) { 
        dyn[i][k] = min(dyn[i][k], dyn[j][k - 1] + get(j + 1, i)); 
       } 
       dyn[i][k] = min(dyn[i][k], dyn[i - 1][k - 1] + sparse[i][0]);
     }
    }
   }
  // cout << dyn[N][m] << '\n'; 
   */ 
  } 
  dp[0] = 0; 
  int64_t ret = prefix[N] - prefix[0]; 
  for(int i = 1; i <= N; i++) { 
   int en = i; 
   int c = 0; 
   dp[i] = min(dp[i], sparse[i][0] + dp[i - 1]);
   if(i >= K) sdp[i][0] = min(sdp[i][0], dp[i - K]);
   for(int b = 1; (1 << b) * (K - 1) <= i; b++) { 
    sdp[i][b] = min({sdp[i][b], sdp[i - (1 << (b - 1)) * (K - 1)][b - 1], sdp[i][b - 1]}); 
   }  
   int turn = 0; 
   while(en > 0) {
    int lo = 1, hi = en;  
    int64_t val = get(en, i); 
    while(lo < hi) { 
     int mid = (lo + hi + 1) / 2; 
     if(get(mid, i) == val) { 
      hi = mid - 1;  
     } else { 
      lo = mid; 
     }
    }
    if(i - lo >= K - 1) {
     int x = (i - lo) / (K - 1); 
     int64_t cost = oo; 
     int st = i; 
     for(int j = 0; j < LOG; j++) { 
      if(x >> j & 1) { 
       cost = min(cost, sdp[st][j]); 
       st -= (1 << j) * (K - 1); 
      }
     } 
     dp[i] = min(dp[i], cost + get(i - (K - 1) * x , i));
    }
    en = lo - 1;
   }
   ret = min(ret, dp[i] + prefix[N] - prefix[i]); 
  } 
  cout << ret << '\n'; 
  return 0; 
}