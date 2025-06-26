#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M;
  int ret = 0, pret = 0; 
  for(int iter = 0; iter < M; iter++) { 
    int sum, first, rem_sum = 0; 
    cin >> sum >> first;
    for(int i = 1, x; i < N; i++) {
      cin >> x;
      rem_sum += x; 
    }
    int opt = 0; 
    for(auto c : {1, 10, 100, 1000, 10000}) { 
      if(c + rem_sum <= sum) {
        opt = max(opt, c); 
      }
    }
    ret += opt; 
    pret += (first + rem_sum <= sum) * first; 
  } 
  cout << ret - pret << '\n'; 
  return 0; 
}