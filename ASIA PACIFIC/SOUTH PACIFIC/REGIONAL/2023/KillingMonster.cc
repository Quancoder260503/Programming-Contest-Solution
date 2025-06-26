#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long 

const int mod = 1e9 + 7; 

int N, K, L, R; 

vector<int64_t> operator * (const vector<int64_t>&a, const vector<int64_t>&b) { 
  vector<int64_t>ret(K);
  for(int i = 0; i < K; i++) { 
    for(int j = 0; j < K; j++) { 
      (ret[(i + j) % K] += a[i] % mod * b[j] % mod) %= mod; 
    }
  } 
  return ret;
}

array<vector<int64_t>, 2> operator * (const array<vector<int64_t>, 2> &a, const array<vector<int64_t>, 2> &b) { 
  array<vector<int64_t>, 2>ret; 
  ret[0].resize(K); 
  ret[1].resize(K);
  for(int i = 0; i < K; i++) { 
    for(int j = 0; j < K; j++) { 
      (ret[0][(i + j) % K] += a[0][i] % mod * b[0][j] % mod) %= mod;
      (ret[1][(i + j) % K] += a[0][i] % mod * b[1][j] % mod) %= mod; 
    }
  } 
  for(int i = 0; i < K; i++) { 
    (ret[1][i] += a[1][i]) %= mod; 
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);   
  cin >> N >> K >> L >> R;
  vector<int>a(N);
  vector<int64_t> b(K); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    b[a[i] % K]++; 
  } 
  vector<int64_t>ret(K); 
  vector<int64_t>c(b.begin(), b.end()); 
  ret[0] = 1; 
  int pw = L; 
  while(pw) { 
    if(pw & 1) ret = ret * c; 
    pw = pw / 2; 
    c = c * c; 
  }
  array<vector<int64_t>, 2>mat, ans; 
  mat[0].resize(K);
  mat[1].resize(K);
  for(int i = 0; i < K; i++) { 
    mat[0][i] = mat[1][i] = b[i]; 
  }
  pw = R - L; 
  ans[0].resize(K); 
  ans[1].resize(K); 
  for(int i = 0; i < K; i++) { 
    ans[0][i] = ans[1][i] = ret[i]; 
  }
  while(pw) { 
    if(pw & 1) ans = ans * mat; 
    pw = pw / 2; 
    mat = mat * mat; 
  }
  cout << ans[1][0] << '\n'; 
  return 0; 
}
