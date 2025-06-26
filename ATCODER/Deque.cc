#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e3 + 10;
const int64_t oo = LLONG_MAX / 2; 

int64_t dyn[maxf][maxf][2], sum[maxf][maxf]; 
vector<int>a;

int64_t memo(int i, int j, int turn) { 
  if(i > j) return 0; 
  int64_t &ret = dyn[i][j][turn]; 
  if(ret != -1) return ret; 
  if(turn) { 
    ret = min(memo(i, j - 1, turn ^ 1), 
              memo(i + 1, j, turn ^ 1)); 
  }
  else { 
    ret = max(a[i] + memo(i + 1, j, turn ^ 1),
              a[j] + memo(i, j - 1, turn ^ 1)); 
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N;
  a.resize(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  for(int i = 0; i < N; i++) 
  for(int j = i; j < N; j++) { 
    sum[i][j] = a[j] + sum[i][j - 1]; 
  }
  memset(dyn, -1, sizeof(dyn)); 
  cout << 2 * memo(0, N - 1, 0) - sum[0][N - 1] << '\n'; 
  return 0; 
}