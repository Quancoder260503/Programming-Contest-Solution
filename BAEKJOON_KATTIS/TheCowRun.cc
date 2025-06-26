#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t oo = LLONG_MAX / 1000; 

const int maxf = 1e3 + 2; 
int64_t dyn[maxf][maxf][2]; 
int a[maxf]; 
int N; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  a[++N] = 0; 
  sort(a + 1, a + N + 1);
  for(int i = 0; i < maxf; i++) 
  for(int j = 0; j < maxf; j++) { 
    dyn[i][j][0] = dyn[i][j][1] = oo; 
  }
  for(int i = 1; i <= N; i++) {
    if(a[i] == 0) { 
      dyn[i][1][0] = 0; 
    }
  }
  for(int dist = 1; dist < N; dist++) { 
    int cc = N - dist; 
    for(int i = 1; i + dist <= N + 1; i++) {
      dyn[i - 1][dist + 1][0] = min(dyn[i - 1][dist + 1][0], 
                                      dyn[i][dist][1] + 1LL * (a[i + dist - 1] - a[i - 1]) * cc); 
      dyn[i - 1][dist + 1][0] = min(dyn[i - 1][dist + 1][0], 
                                      dyn[i][dist][0] + 1LL * (a[i] - a[i - 1]) * cc); 
      dyn[i][dist + 1][1]     = min(dyn[i][dist + 1][1], 
                                      dyn[i][dist][1] + 1LL * (a[i + dist] - a[i + dist - 1]) * cc); 
      dyn[i][dist + 1][1]     = min(dyn[i][dist + 1][1], 
                                      dyn[i][dist][0] + 1LL * (a[i + dist] - a[i]) * cc); 
    } 
  }
  cout << min(dyn[1][N][0], dyn[1][N][1]) << '\n'; 
  return 0; 
}

