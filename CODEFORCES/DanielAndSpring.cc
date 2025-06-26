#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 31; 

int64_t dyn[maxf][3][2][3][2];
int A, B; 

int64_t memo(int pos, int greaterA, int is_equalA, int greaterB, int is_equalB) {
  if(pos == -1) return (greaterA > 0) && (greaterB > 0);  
  int64_t &ret = dyn[pos][greaterA][is_equalA][greaterB][is_equalB]; 
  if(ret != -1) return ret; 
  ret = 0; 
  int c = (B >> pos) & 1, d = (A >> pos) & 1; 
  for(int bitA = 0; bitA < 2; bitA++) { 
    for(int bitB = 0; bitB + bitA < 2; bitB++) { 
      int next_greaterA = greaterA, next_greaterB = greaterB;
      if(greaterA == 1) { 
        next_greaterA = (bitA == d ? 1 : (bitA > d ? 2 : 0));
      }
      if(greaterB == 1) { 
        next_greaterB = (bitB == d ? 1 : (bitB > d ? 2 : 0)); 
      }
      if(is_equalA && is_equalB) { 
        if(c == 0 && bitA) continue; 
        if(c == 0 && bitB) continue;
        ret += memo(pos - 1, next_greaterA, is_equalA && (c == bitA), next_greaterB, is_equalB && (c == bitB));  
      } 
      else if(is_equalA) { 
        if(c == 0 && bitA) continue; 
        ret += memo(pos - 1, next_greaterA, is_equalA && (c == bitA), next_greaterB, is_equalB); 
      } 
      else if(is_equalB) { 
        if(c == 0 && bitB) continue; 
        ret += memo(pos - 1, next_greaterA, is_equalA, next_greaterB, is_equalB && (c == bitB)); 
      }
      else { 
        ret += memo(pos - 1, next_greaterA, is_equalA, next_greaterB, is_equalB); 
      }
    }
  }
  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Q; 
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) {
    cin >> A >> B;
    memset(dyn, -1, sizeof(dyn));  
    int64_t ret = memo(maxf - 1, 1, true, 1, true); 
    cout << ret << '\n'; 
  }
  return 0; 
}
/*
 (0, 0), (0, 1), (0, 2), (0, 3), (0, 4), 
 (1, 0), (1, 2), (1, 4),
 (2, 0), (2, 1), (2, 4), 
 (3, 0), (3, 4), 
 (4, 0), (4, 1), (4, 2), (4, 3). 
*/