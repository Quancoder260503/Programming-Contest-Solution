#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

struct bracket { 
  int open, close, sum, length;
  bracket(int _open, int _close, int _sum, int _length) : open(_open), close(_close), sum(_sum), length(_length) {}; 
  bool operator < (const bracket &other) const { 
    if((sum > 0) ^ (other.sum > 0)) { 
      return sum < other.sum; 
    }
    if(sum > 0) { 
      if(close == other.close) return sum < other.sum; 
      return close > other.close; 
    }
    else { 
      if(open == other.open) return sum < other.sum; 
      return open < other.open; 
    }
  }
}; 

int64_t dyn[2][100005]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N;  
  cin >> N;  
  string s; 
  vector<bracket>seq; 
  int sum_len = 0; 
  for(int i = 0; i < N; i++) {  
    cin >> s;
    int sum = 0, open = 0, close = 0; 
    for(int j = 0; j < sz(s); j++) { 
      if(s[j] == '(') { 
        open++;
        sum++; 
      }  
      else { 
        if(open > 0) open--; 
        else close++; 
        sum--; 
      }
    }
    sum_len += sz(s); 
    seq.emplace_back(open, close, sum, sz(s));
  }
  sort(seq.rbegin(), seq.rend());
  memset(dyn, -63, sizeof(dyn)); 
  dyn[0][0] = 0;
  for(int i = 0; i < N; i++) { 
    for(int j = sum_len; j >= 0; j--) {
      dyn[(i + 1) & 1][j] = max(dyn[(i + 1) & 1][j], dyn[i & 1][j]);  
      if(j >= seq[i].close && j + seq[i].sum <= sum_len && j + seq[i].sum >= 0) { 
        dyn[(i + 1) & 1][j + seq[i].sum] = max(dyn[(i + 1) & 1][j + seq[i].sum], dyn[i & 1][j] + seq[i].length); 
      }
    }
    for(int j = 0; j <= sum_len; j++) { 
      dyn[i & 1][j] = dyn[(i + 1) & 1][j]; 
    }
  }
  cout << dyn[N & 1][0] << '\n'; 
  return 0; 
}
