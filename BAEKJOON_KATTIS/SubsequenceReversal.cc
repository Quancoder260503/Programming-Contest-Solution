#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 52; 
const int oo = 1e7;

int dyn[maxf][maxf][maxf][maxf]; 
int N, a[maxf]; 

int memo(int i, int j, int max_left, int min_right) { 
  if(max_left > min_right) return -oo;
  if(i >  j) return 0; 
  if(i == j) { 
    return (max_left <= a[i] && a[i] <= min_right ? 1 : 0); 
  }
  int &ret = dyn[i][j][max_left][min_right]; 
  if(ret != -1) return ret; 
  ret = max(0, memo(i + 1, j - 1, max_left, min_right));
  if(max_left <= a[j]) { 
    ret = max(ret, 1 + memo(i + 1, j - 1, a[j], min_right)); 
  }
  if(a[i] <= min_right) { 
    ret = max(ret, 1 + memo(i + 1, j - 1, max_left, a[i])); 
  }
  if(max_left <= a[j] && a[j] <= a[i] && a[i] <= min_right) { 
    ret = max(ret, 2 + memo(i + 1, j - 1, a[j], a[i])); 
  }
  ret = max(ret, memo(i + 1, j, max_left, min_right));
  ret = max(ret, memo(i, j - 1, max_left, min_right)); 
  if(max_left <= a[i]) { 
    ret = max(ret, 1 + memo(i + 1, j, a[i], min_right)); 
  }
  if(a[j] <= min_right) { 
    ret = max(ret, 1 + memo(i, j - 1, max_left, a[j])); 
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  memset(dyn, -1, sizeof(dyn)); 
  cout << memo(1, N, 0, 50) << '\n'; 
  return 0; 
}

