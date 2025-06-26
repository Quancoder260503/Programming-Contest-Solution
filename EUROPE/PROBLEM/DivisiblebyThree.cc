#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int maxf = 5e5 + 10; 

int N; 
int64_t a[maxf], prefixSquare[maxf], prefix[maxf]; 

map<pair<int64_t, int64_t>, int>ctr; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
    prefix[i] = (prefix[i - 1] + a[i]) % 6; 
    prefixSquare[i] = (prefixSquare[i - 1] + 1LL * a[i] * a[i]) % 6; 
  } 
  ctr[{0, 0}]++; 
  int64_t ret = 0; 
  for(int i = 1; i <= N; i++) {
    int64_t curr = (1LL * prefix[i] % 6 * prefix[i] % 6 - prefixSquare[i] + 6) % 6;
    int64_t prod = (2 * prefix[i]) % 6; 
    for(const auto &[u, v] : ctr) { 
      int64_t nxt = (curr + u.second + 6) % 6; 
      int64_t cc  = prod * u.first % 6;
      if((nxt - cc + 6) % 6 == 0) { 
        ret += v; 
      } 
    } 
    ctr[{prefix[i] % 6, (1LL * prefix[i] * prefix[i] + prefixSquare[i]) % 6}]++; 
  } 
  cout << ret << '\n'; 
  return 0; 
}