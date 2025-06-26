#include "bits/stdc++.h"

using namespace std;

#define int64_t long long 
#define sz(x) int(x.size())

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, int sz, bool invert) {
  for (int i = 1, mask = 0; i < sz; i++) {
    int bit = sz >> 1;
    for (; mask & bit; bit = bit / 2) {
      mask = mask xor bit;
    }
    mask = mask xor bit;
    if (i < mask) {
      swap(a[i], a[mask]);
    }
  }
  for (int len = 2; len <= sz; len = len * 2) {
    double angle = 2 * PI / len * (invert ? -1 : 1);
    cd wang(cos(angle), sin(angle));
    for (int i = 0; i < sz; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i + j];
        cd v = w * a[i + j + len / 2];
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w = w * wang;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < sz; i++) {
      a[i] /= sz;
    }
  }
  return;
}
vector<int64_t> FFT(vector<int> &a, vector<int> &b) {
  vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());
  int n = 1;
  while (n < A.size() + B.size()) {
    n = n * 2;
  }
  A.resize(n);
  B.resize(n);
  fft(A, (int)A.size(), false);
  fft(B, (int)B.size(), false);
  for (int i = 0; i < n; i++) {
    A[i] *= B[i];
  }
  fft(A, (int)A.size(), true);
  vector<int64_t> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = 1LL * round(A[i].real());
  }
  return res;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string a, b;
  cin >> a >> b;
  vector<int>cntA(6), cntB(6); 
  vector<vector<vector<int>>>dp(6, vector<vector<int>>(6, vector<int>(sz(a)))); 
  for(int i = 0; i < sz(a); i++) { 
    cntA[a[i] - 'a']++; 
  }
  for(int i = 0; i < sz(b); i++) { 
    cntB[b[i] - 'a']++; 
  }
  for(int i = 0; i < 6; i++) {
    if(!cntA[i]) continue; 
    for(int j = 0; j < 6; j++) {  
      if(!cntB[j]) continue; 
      vector<int> pa(sz(a)), pb(sz(b)); 
      for(int k = 0; k < sz(a); k++) { 
        if(a[k] == char(i + 'a')) { 
          pa[k] = 1;   
        }
      }
      for(int k = 0; k < sz(b); k++) { 
        if(b[k] == char(j + 'a')) { 
          pb[sz(b) - k - 1] = 1; 
        }
      }
      vector<int64_t> pc = FFT(pa, pb); 
      for(int k = 0; k < min(sz(a), sz(pc)); k++) { 
        if(pc[k] > 0) {
          dp[i][j][k] += pc[k]; 
        }
      }
    }
  }
  vector<int>mp(6); 
  for(int i = 0; i < sz(b); i++) { 
    mp[b[i] - 'a']++; 
  }
  for(int i = 0; i < sz(b) - 1; i++) { 
    mp[a[i] - 'a']++; 
  }
  int sum = 0; 
  for(int i = 0; i < 6; i++) { 
    sum += (mp[i] > 0); 
  }
  for(int i = sz(b) - 1; i < sz(a); i++) { 
    mp[a[i] - 'a']++;
    if(mp[a[i] - 'a'] == 1) { 
      sum++; 
    } 
    if(i >= sz(b)) { 
      mp[a[i - sz(b)] - 'a']--;
      if(mp[a[i - sz(b)] - 'a'] == 0) { 
        sum--; 
      }
    }
    vector<int>vis(6, false); 
    int cnt = 0; 
    function<void(int)> dfs = [&](int u) { 
      vis[u] = true;
      for(int j = 0; j < 6; j++) { 
        if(!vis[j] && mp[j]) { 
          if(dp[u][j][i] > 0 || dp[j][u][i] > 0) { 
            dfs(j);   
          }
        }
      }
      return; 
    }; 
    for(int j = 0; j < 6; j++) { 
      if(vis[j] || !mp[j]) continue; 
      cnt++; 
      dfs(j); 
    }
    cout << sum - cnt << ' '; 
  }
  cout << '\n'; 
  return 0;
}