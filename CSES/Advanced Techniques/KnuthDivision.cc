#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int maxf = 5e3 + 10;
const int64_t oo = LLONG_MAX / 1000;

int64_t dyn[maxf][maxf], prefix[maxf], cost[maxf][maxf]; 
int opt[maxf][maxf];
int N;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for (int i = 1, x; i <= N; i++) {
    cin >> x; 
    prefix[i] = prefix[i - 1] + 1LL * x;
  }
  for(int i = 1; i <= N; i++) { 
    for(int j = i; j <= N; j++) { 
      cost[i][j] = prefix[j] - prefix[i - 1]; 
    }
  }
  for (int i = 1; i <= N; i++) {
    opt[i][i] = i;
  }
  for (int i = N - 1; i >= 1; i--) { 
    for (int j = i + 1; j <= N; j++) {
      dyn[i][j] = oo / 2;
      for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++)
        if (dyn[i][j] >= dyn[i][k] + dyn[k + 1][j] + cost[i][j]) {
          dyn[i][j] = dyn[i][k] + dyn[k + 1][j] + cost[i][j]; 
          opt[i][j] = k;
        }
    }
  } 
  cout << dyn[1][N] << '\n'; 
  return 0;
}