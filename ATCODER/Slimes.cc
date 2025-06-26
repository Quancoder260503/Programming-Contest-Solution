#include "bits/stdc++.h"

using namespace std;

const int64_t oo = LLONG_MAX / 2; 

vector<vector<int64_t>>dyn, sum;
vector<int>a; 
int N; 

int64_t memo(int i, int j) { 
    if(i >= j) return 0; 
    int64_t &ret = dyn[i][j]; 
    if(ret != -1) return ret; 
    ret = oo; 
    for(int k = i; k < j; k++) { 
      ret = min(ret, sum[i][j] + memo(i, k) + memo(k + 1, j)); 
    }
    return ret;
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N; 
  dyn.resize(N, vector<int64_t>(N, -1)); 
  sum.resize(N, vector<int64_t>(N)); 
  a.resize(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  for(int i = 0; i < N; i++) { 
    for(int j = i; j < N; j++) { 
       sum[i][j] = a[j] + (j ? sum[i][j - 1] : 0); 
    }
  }
  cout << memo(0, N - 1) << '\n'; 
  return 0; 
}