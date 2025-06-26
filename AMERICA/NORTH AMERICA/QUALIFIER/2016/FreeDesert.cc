#include "bits/stdc++.h"

using namespace std;

const int THRES = 5000;
#define sz(x) int(x.size())
#define int64_t long long

int64_t dyn[2][2][1 << 10][1 << 10][2][2];
int64_t res;
int mask, ctr = 0;
string P;
/*
int64_t memo(int pos, int carry, int maskA, int maskB, int stopA, int stopB) {
    if(pos == P.size()) return ((carry == 0) && stopA && stopB);
    int64_t &ret = dyn[pos][carry][maskA][maskB][stopA][stopB];
    if(ret != -1) return ret;
    ret = 0;
    if(stopA && stopB) {
        if(carry == P[pos] - '0') {
            ret += memo(pos + 1, 0, maskA, maskB, stopA, stopB);
        }
    }
    else if(stopA) {
        for(int digitB = 1; digitB < 10; digitB++) {
            if(mask & (1 << digitB) || maskA & (1 << digitB)) continue;
            int c = (digitB + carry) % 10;
            if(c == P[pos] - '0') {
                ret += memo(pos + 1, (digitB + carry) / 10, maskA, maskB | (1 <<
digitB), stopA, stopB); if(digitB > 0) { ret += memo(pos + 1, (digitB + carry) /
10, maskA, maskB | (1 << digitB), stopA, true);
                }
            }
        }
    }
    else if(stopB) {
        for(int digitA = 1; digitA < 10; digitA++) {
            if(mask & (1 << digitA) || maskB & (1 << digitA)) continue;
            int c = (digitA + carry) % 10;
            if(c == P[pos] - '0') {
                ret += memo(pos + 1, (digitA + carry) / 10, maskA | (1 <<
digitA), maskB, stopA, stopB); if(digitA > 0) { ret += memo(pos + 1, (digitA +
carry) / 10, maskA | (1 << digitA), maskB, true, stopB);
                }
            }
        }
    }
    else {
        for(int digitA = 0; digitA < 10; digitA++) {
            if(maskB & (1 << digitA) || mask & (1 << digitA)) continue;
            for(int digitB = 0; digitB < 10; digitB++) {
                if(maskA & (1 << digitB) || mask & (1 << digitB)) continue;
                if(digitA != digitB) {
                    int c = (digitA + digitB + carry) % 10;
                    if(c == P[pos] - '0') {
                        ret += memo(pos + 1, (digitA + digitB + carry) / 10,
maskA | (1 << digitA), maskB | (1 << digitB), stopA, stopB); if(digitA > 0) {
                           ret += memo(pos + 1, (digitA + digitB + carry) / 10,
maskA | (1 << digitA), maskB | (1 << digitB), true, stopB);
                        }
                        if(digitB > 0) {
                           ret += memo(pos + 1, (digitA + digitB + carry) / 10,
maskA | (1 << digitA), maskB | (1 << digitB), stopA, true);
                        }
                        if(digitA > 0 && digitB > 0) {
                           ret += memo(pos + 1, (digitA + digitB + carry) / 10,
maskA | (1 << digitA), maskB | (1 << digitB), true, true);
                        }
                    }
                }
            }
        }
    }
    return ret;
}
*/
void rec(int pos, int64_t S, int64_t a, int maskA, int64_t b, int maskB, int64_t c, int maskC) {
  if(pos == sz(P)) { 
    if(mask & maskA || mask & maskB || maskA & maskB) return; 
    if(a < b) cout << a << " " << b << '\n'; 
    ctr++; 
    if(ctr == 5000) { exit(0); }
  }
  else { 
    int64_t next_s = 10 * S + (P[pos] - '0'); 
    int curr_d = P[pos] - '0'; 
    for(int digit = 0; digit < 10; digit++) { 
      int64_t nA = 10 * a + digit; 
      int nmaskA = maskA | (nA ? (1 << digit) : 0);
      if(nmaskA & mask) continue; 
      int64_t nB = next_s - nA;
      int64_t nC = next_s - nA - 1; 
      int nmaskB, nmaskC; 
      if(curr_d >= digit) { 
        nmaskB = maskB | (nB ? (1 << (curr_d - digit)) : 0); 
      }
      else { 
        nmaskB = maskC | (nB ? (1 << (10 + curr_d - digit)) : 0); 
      }
      if(curr_d >= digit + 1) { 
        nmaskC = maskB | (nC ? (1 << (curr_d - digit - 1)) : 0); 
      }
      else { 
        nmaskC = maskC | (nC ? (1 << (10 + curr_d - digit - 1)) : 0); 
      } 
      if((mask   & nmaskB) && (mask   & nmaskC)) continue;
      if((nmaskA & nmaskB) && (nmaskA & nmaskC)) continue;  
      rec(pos + 1, next_s, nA, nmaskA, nB, nmaskB, nC, nmaskC); 
    }  
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // memset(dyn, -1, sizeof(dyn));
  cin >> P;
  reverse(P.begin(), P.end());
  for (int i = 0; i < P.size(); i++) {
    int c = P[i] - '0';
    mask = mask | (1 << c);
  }
  //  res = memo(0, 0, 0, 0, 0, 0);
  for (int maskA = 0; maskA < (1 << 10); maskA++)
    for (int maskB = 0; maskB < (1 << 10); maskB++)
      if ((maskA & maskB) == 0) {
        dyn[sz(P) % 2][0][maskA][maskB][true][true]++;
      }
  for (int pos = sz(P) - 1; pos >= 0; pos--) {
    for (int carry = 0; carry < 2; carry++)
      for (int stopA = 0; stopA < 2; stopA++)
        for (int stopB = 0; stopB < 2; stopB++)
          for (int maskA = 0; maskA < (1 << 10); maskA++)
            for (int maskB = 0; maskB < (1 << 10); maskB++) if((maskA & maskB) == 0) {
              int64_t &ret = dyn[pos % 2][carry][maskA][maskB][stopA][stopB];
              ret = 0;
              if (stopA && stopB) {
                if (carry == P[pos] - '0') {
                  ret += dyn[(pos + 1) % 2][0][maskA][maskB][stopA][stopB];
                }
              } else if (stopA) {
                for (int digitB = 1; digitB < 10; digitB++) {
                  if (mask & (1 << digitB) || maskA & (1 << digitB)) continue;
                  int c = (digitB + carry) % 10;
                  if (c == P[pos] - '0') {
                    ret += dyn[(pos + 1) % 2][(digitB + carry) / 10][maskA][maskB | (1 << digitB)][stopA][stopB];
                    if (digitB > 0) {
                      ret += dyn[(pos + 1) % 2][(digitB + carry) / 10][maskA][maskB | (1 << digitB)][stopA][true];
                    }
                  }
                }
              } else if (stopB) {
                for (int digitA = 1; digitA < 10; digitA++) {
                  if (mask & (1 << digitA) || maskB & (1 << digitA)) continue;
                  int c = (digitA + carry) % 10;
                  if (c == P[pos] - '0') {
                    ret += dyn[(pos + 1) % 2][(digitA + carry) / 10][maskA | (1 << digitA)][maskB][stopA][stopB];
                    if (digitA > 0) {
                      ret += dyn[(pos + 1) % 2][(digitA + carry) / 10][maskA | (1 << digitA)][maskB][true][stopB];
                    }
                  }
                }
              } else {
                for (int digitA = 0; digitA < 10; digitA++) {
                  if (maskB & (1 << digitA) || mask & (1 << digitA)) continue;
                  for (int digitB = 0; digitB < 10; digitB++) {
                    if (maskA & (1 << digitB) || mask & (1 << digitB)) continue;
                    if (digitA != digitB) {
                      int c = (digitA + digitB + carry) % 10;
                      if (c == P[pos] - '0') {
                        ret += dyn[(pos + 1) % 2][(digitA + digitB + carry) / 10][maskA | (1 << digitA)][maskB | (1 << digitB)][stopA][stopB];
                        if (digitA > 0) {
                             ret += dyn[(pos + 1) % 2][(digitA + digitB + carry) / 10][maskA | (1 << digitA)][maskB | (1 << digitB)][true][stopB];
                        }
                        if (digitB > 0) {
                             ret += dyn[(pos + 1) % 2][(digitA + digitB + carry) / 10][maskA | (1 << digitA)][maskB | (1 << digitB)][stopA][true];
                        }
                        if (digitA > 0 && digitB > 0) {
                             ret += dyn[(pos + 1) % 2][(digitA + digitB + carry) / 10][maskA | (1 << digitA)][maskB | (1 << digitB)][true][true];
                        }
                      }
                    }
                  }
                }
              }
            }
  }
  res = dyn[0][0][0][0][0][0]; 
  res = res / 2;
  cout << res << '\n';
  reverse(P.begin(), P.end()); 
  rec(0, 0, 0, 0, 0, 0, 0, 0);
  return 0;
}