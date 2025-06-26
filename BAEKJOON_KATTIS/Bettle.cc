#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t oo = LLONG_MAX / 1000; 

const int maxf = 302; 
int64_t dyn[maxf][maxf][maxf][2]; 
int a[maxf]; 
int N, M; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> M; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  a[++N] = 0; 
  sort(a + 1, a + N + 1);
  for(int i = 0; i < maxf; i++) 
  for(int j = 0; j < maxf; j++) 
  for(int k = 0; k < maxf; k++) { 
    dyn[i][j][k][0] = dyn[i][j][k][1] = oo; 
  }
  int st = 0; 
  for(int i = 1; i <= N; i++) { 
    if(a[i] == 0) { 
      st = i; 
      break;
    }  
  }
  for(int i = 1; i <= N; i++) { 
    for(int j = 1; j <= N; j++) { 
      dyn[i][j][0][1] = dyn[i][j][0][0] = 0; 
    }
  }
  for(int k = 1; k < N; k++) { 
    for(int i = 1; i <= N; i++) { 
      for(int j = i; j <= N; j++) { 
        dyn[i][j][k][0] = min(dyn[i][j][k][0], dyn[i - 1][j][k - 1][0] + (a[i] - a[i - 1]) * k);
        dyn[i][j][k][1] = min(dyn[i][j][k][1], dyn[i - 1][j][k - 1][0] + (a[j] - a[i - 1]) * k); 
        dyn[i][j][k][0] = min(dyn[i][j][k][0], dyn[i][j + 1][k - 1][1] + (a[j + 1] - a[i]) * k); 
        dyn[i][j][k][1] = min(dyn[i][j][k][1], dyn[i][j + 1][k - 1][1] + (a[j + 1] - a[j]) * k); 
      }
    }
  }
  int64_t ret = 0; 
  for(int k = 0; k < N; k++) { 
    ret = max(ret, 1LL * M * k - min(dyn[st][st][k][0], dyn[st][st][k][1])); 
  }
  cout << ret << '\n'; 
  return 0; 
}


/*
    dyn[i][j][k][2] = {mininum time to visit k points in the range [i, j] with 0 if we ended up on the left side / 1 if 
                      we ended up on the right side};
    dyn[i - 1][j][k][0] = min(dyn[i][j][k - 1][0] + k * (a[i] - a[i - 1])); 
    dyn[i][j + 1][k][1] = min(dyn[i][j][k - 1][0] + k * (a[j + 1] - a[i])); 
    dyn[i - 1][j][k][0] = min(dyn[i][j][k - 1][1] + k * (a[j] - a[i - 1]));
    dyn[i][j + 1][k][1] = min(dyn[i][j][k - 1][1] + k * (a[j + 1] - a[i]));  
*/ 
