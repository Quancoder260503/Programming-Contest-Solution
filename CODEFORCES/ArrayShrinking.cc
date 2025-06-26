#include "bits/stdc++.h"

using namespace std; 

const int maxf = 750; 

int a[maxf], dyn[maxf][maxf], best[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N;
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
    dyn[i][i] = a[i]; 
  }
  for(int i = N; i > 0; i--) { 
    for(int j = i + 1; j <= N; j++) { 
      for(int k = i + 1; k <= j; k++) { 
        if(dyn[i][k - 1] > 0 && dyn[i][k - 1] == dyn[k][j]) { 
          dyn[i][j] = max(dyn[i][j], dyn[i][k - 1] + 1); 
        } 
      }
    }
  }
  memset(best, 63, sizeof(best)); 
  best[0] = 0; 
  for(int i = 1; i <= N; i++) { 
    for(int j = 1; j <= i; j++) { 
      if(dyn[j][i]) { 
        best[i] = min(best[i], best[j - 1] + 1); 
      } 
    }
  }
  cout << best[N] << '\n'; 
  return 0; 
}
