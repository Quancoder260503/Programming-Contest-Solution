#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
 
const int max_s = 301; 
const int max_f = 2e5 + 10; 

int64_t dyn[2][max_f]; 
vector<vector<int64_t>>prefix;

void dnq(int L, int R, int x, int y, int now, int mod, int rem) { 
  if(L > R) return; 
  int mid = (L + R) / 2; 
  int pos = mid; 
  dyn[now ^ 1][mid * mod + rem] = dyn[now][mid * mod + rem]; 
  for(int j = min(y, mid - 1); j >= x; j--) { 
    if(mid - j > sz(prefix[mod])) break; 
    if(dyn[now ^ 1][mid * mod + rem] < dyn[now][j * mod + rem] + prefix[mod][mid - j - 1]) { 
      dyn[now ^ 1][mid * mod + rem] = dyn[now][j * mod + rem] + prefix[mod][mid - j - 1]; 
      pos = j; 
    }
  }
  dnq(L, mid - 1, x, pos, now, mod, rem); 
  dnq(mid + 1, R, pos, y, now, mod, rem); 
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, K; 
  cin >> N >> K;
  vector<int>s(N), v(N);
  for(int i = 0; i < N; i++) { 
    cin >> s[i] >> v[i];
  } 
  prefix.resize(max_s + 1); 
  for(int i = 0; i < N; i++) { 
    prefix[s[i]].push_back(v[i]); 
  }
  for(int i = 1; i <= max_s; i++) { 
    sort(prefix[i].rbegin(), prefix[i].rend()); 
    for(int j = 1; j < sz(prefix[i]); j++) { 
      prefix[i][j] += prefix[i][j - 1]; 
    }
  }
  int curr = 0; 
  for(int i = 1; i <= max_s; i++) { 
    if(!sz(prefix[i])) continue; 
    for(int j = 0; j < i; j++) { 
      dnq(0, (K - j) / i, 0, (K - j) / i, curr, i, j); 
    }
    for(int j = 1; j <= K; j++) { 
      dyn[curr ^ 1][j] = max(dyn[curr ^ 1][j], dyn[curr ^ 1][j - 1]); 
    }
    curr = curr ^ 1; 
  }
  for(int i = 1; i <= K; i++) { 
    cout << dyn[curr][i] << ' '; 
  }
  cout << '\n'; 
  return 0; 
}