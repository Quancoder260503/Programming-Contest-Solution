#include "bits/stdc++.h"

using namespace std;

#define int64_t long long 

const int LOG = 62;
const int maxf = 12;
const int mod = 998244353;

int64_t dyn[LOG][2][2][2][maxf][maxf][maxf], N;
int A, B, C;

int64_t memo(int pos, int is_equalA, int is_equalB, int is_equalC, int rem_A,
             int rem_B, int rem_C) {
  if (pos == -1) return (rem_A == 0) & (rem_B == 0) & (rem_C == 0);
  int64_t &ret = dyn[pos][is_equalA][is_equalB][is_equalC][rem_A][rem_B][rem_C];
  if (ret != -1) return ret;
  ret = 0; 
  int on = (N >> pos) & 1;
  for(int bitA = 0; bitA <= (is_equalA ? 1 : on); bitA++) 
  for(int bitB = 0; bitB <= (is_equalB ? 1 : on); bitB++)
  for(int bitC = 0; bitC <= (is_equalC ? 1 : on); bitC++) if((bitA ^ bitB ^ bitC) == 0){
    ret += memo(pos - 1, is_equalA || (bitA < on), is_equalB || (bitB < on), is_equalC || (bitC < on), 
                (2 * rem_A + bitA) % A, (2 * rem_B + bitB) % B, (2 * rem_C + bitC) % C); 
    ret %= mod;
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> A >> B >> C;
  memset(dyn, -1, sizeof(dyn));
  int64_t ret = (memo(LOG - 1, 0, 0, 0, 0, 0, 0) - 1 + mod) % mod;
  ret = (ret + mod - (N / lcm(A, B)) % mod) % mod; 
  ret = (ret + mod - (N / lcm(B, C)) % mod) % mod; 
  ret = (ret + mod - (N / lcm(C, A)) % mod) % mod; 
  cout << ret << '\n'; 
  return 0;
}