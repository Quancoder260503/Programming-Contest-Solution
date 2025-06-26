#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int64_t dyn[30][2][10][30];
string S; 

int64_t memo(int pos, int is_equal, int cur_mod, int num) { 
  if(pos == sz(S)) return (cur_mod == 0) * num; 
  int64_t &ret = dyn[pos][is_equal][cur_mod][num]; 
  if(ret != -1) return ret;
  ret = 0; 
  int bound = (is_equal ? S[pos] - '0' : 9); 
  for(int next = 0; next <= bound; next++) { 
    ret += memo(pos + 1, is_equal & (next == bound), 
               (10 * cur_mod + next) % 8, num + (next == 8 || next == 6)); 
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
    cin >> S; 
    memset(dyn, -1, sizeof(dyn));
    int64_t ret = 0; 
    for(int i = 0; i < sz(S); i++) { 
      ret += (S[i] == '6' || S[i] == '8'); 
    }
    ret = ret - (stoll(S) % 8 == 0) * ret; 
    ret += memo(0, true, 0, 0); 
    cout << ret << '\n'; 
  }
  return 0; 
}

