#include "bits/stdc++.h" 

using namespace std; 

int cache[10003][1002]; 
int N, C; 
int64_t a[1002]; 

bool f(int rem, int level) { 
 if(rem == 0) return true; 
 if(cache[rem][level] != -1) return cache[rem][level]; 
 int &ret = cache[rem][level]; 
 ret = false;  
 for(int i = 0; i < N; i++) { 
  int64_t val = ceil(1.0 * a[i] / (1LL << level)); 
  if(val == 1) { 
    return ret = true; 
  }
  if(rem >= val && f(rem - val, level + 1)) { 
    cout << rem << " " << level << " " << a[i] << '\n'; 
    return ret = true; 
  }
 }
 return ret; 
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> C; 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  memset(cache, -1, sizeof(cache));  
  cout << (f(C, 0) ? "YES" : "NO") << '\n'; 
  return 0;   
}
