#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int mod = 1e9 + 9; 
const int maxf = 250; 

int64_t dyn[maxf][maxf]; 
vector<int>cost;
int A, B; 
string S; 

int64_t memo(int scoreA, int scoreB) { 
  if(scoreA == 0 && scoreB == 0) return 1; 
  int64_t &ret = dyn[scoreA][scoreB]; 
  if(ret != -1) return ret;   
  ret = 0; 
  for(auto c : cost) { 
    if(scoreA >= c) { 
      ret += memo(scoreA - c, scoreB); 
      ret %= mod; 
    }
    if(scoreB >= c) { 
      ret += memo(scoreA, scoreB - c); 
      ret %= mod; 
    }
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> A >> B;
  while(cin >> S) { 
    if(sz(S) >= 3) { 
      int base_cost = 0; 
      string num; 
      for(int i = 0; i < sz(S); i++) { 
        if(S[i] == ':') { 
          cost.push_back(base_cost + stoi(num)); 
          if(base_cost == 0) { base_cost += stoi(num); } 
          num = ""; 
        }
        else { 
          num = num + S[i]; 
        }
      }
      base_cost += stoi(num); 
      cost.push_back(base_cost); 
    }
    else {
      cost.push_back(stoi(S)); 
    }
  } 
  memset(dyn, -1, sizeof(dyn)); 
  printf("%d vs %d can be achieved %lld ", A, B, memo(A, B));
  printf(memo(A, B) == 1 ? "way\n" : "ways\n");  
  return 0; 
}
