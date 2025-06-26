#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int N = 50;

int64_t Comb[N][N]; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0);
  cout.tie(0); 
  Comb[0][0] = 1; 
  for(int i = 1; i < N; i++) { 
    for(int j = 0; j <= i; j++) { 
      Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0); 
    }
  }
  auto calc = [&](int num_digit, int num_up, int num_lo, int L) { 
    int64_t ways = 0; 
    for(int ndigit  = max(0, num_digit); ndigit <= L; ndigit++) { 
      for(int nup   = max(0, num_up);    nup    <= L; nup++) { 
        for(int nlo = max(0, num_lo);    nlo    <= L; nlo++) { 
          if(ndigit + nup + nlo == L) { 
            ways += 1LL * pow(10, ndigit) * pow(26, nup) * pow(26, nlo) * 
                    Comb[L][ndigit] * Comb[L - ndigit][nup];              
          }
        }
      } 
    }
    return ways; 
  }; 
  int64_t K; 
  int num_digit, num_up, num_lo, L; 
  cin >> L >> num_digit >> num_up >> num_lo >> K; 
  string ret;
  for(; L > 0;) {
    L--; 
    num_digit--; 
    int flag = false; 
    int64_t ways = calc(num_digit, num_up, num_lo, L); 
    for(int i = 0; i < 10; i++) {
      if(K > ways) { 
        K = K - ways; 
      }
      else { 
        ret = ret + char('0' + i); 
        flag = true; 
        break; 
      }
    }
    if(flag) continue; 
    num_digit++; 
    num_up--; 
    ways = calc(num_digit, num_up, num_lo, L);  
    for(int i = 0; i < 26; i++) {
      if(K > ways) { 
        K = K - ways; 
      }
      else { 
        ret = ret + char('A' + i); 
        flag = true; 
        break; 
      }
    }
    if(flag) continue; 
    num_up++; 
    num_lo--; 
    ways = calc(num_digit, num_up, num_lo, L); 
    for(int i = 0; i < 26; i++) {
      if(K > ways) { 
        K = K - ways; 
      }
      else { 
        ret = ret + char('a' + i); 
        flag = true; 
        break; 
      }
    }
  }
  cout << ret << '\n'; 
  return 0; 
} 