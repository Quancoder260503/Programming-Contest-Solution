#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1e3 + 10;
const int mod = 1e9 + 7;

int64_t dyn[maxf][maxf]; 
int a[maxf], N; 

int64_t memo(int pos, int carry, int target) { 
  if(pos == 0) return (carry % 31 == target); 
  int64_t &ret = dyn[pos][carry]; 
  if(ret != -1) return ret;
  ret = 0; 
  for(int ch = 32; ch <= 126; ch++) { 
    if(a[pos] == (carry + ch) % 31) { 
      (ret += memo(pos - 1, (carry + ch) / 31, target)) %= mod; 
    }
  }
  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  while(cin >> N && N) { 
    for(int i = 1; i <= N; i++) { 
      cin >> a[i]; 
    }
    int carry = 0; 
    for(int i = N; i > 0; i--) {
      int64_t new_carry = (carry + a[i]) / 31; 
      a[i] = (carry + a[i]) % 31; 
      carry = new_carry; 
    }
    memset(dyn, -1, sizeof(dyn)); 
    cout << memo(N, 0, carry) << '\n'; 
  }
  return 0; 
}
