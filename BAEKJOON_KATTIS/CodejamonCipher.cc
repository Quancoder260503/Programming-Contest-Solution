#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 200; 
const int mod = 1e9 + 7; 
const int mA  = 31; 
const int mB  = 37; 

int64_t pA[maxf], pB[maxf]; 

void init(void) { 
   pA[0] = pB[0] = 1; 
   for(int i = 1; i < maxf; i++) { 
     pA[i] = pA[i - 1] % mod * mA % mod; 
     pB[i] = pB[i - 1] % mod * mB % mod; 
   }
   return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, Q; 
  cin >> Q;
  init(); 
  for(int case_num = 0; case_num < Q; case_num++) {
    string S;
    cin >> N >> M;
    map<pair<int64_t, int64_t>, int>mp;  
    for(int i = 0; i < N; i++) { 
       cin >> S; 
       int64_t ca = 0, cb = 0; 
       for(int j = 0; j < S.size(); j++) { 
         ca += pA[S[j] - 'a' + 1]; 
         cb += pB[S[j] - 'a' + 1]; 
       }
       mp[{ca, cb}]++; 
    }
    cout << "Case #" << case_num + 1 << ": "; 
    for(int iter = 0; iter < M; iter++) { 
       cin >> S;
       S = " " + S; 
       vector<int64_t>dyn(sz(S));
       dyn[0] = 1;   
       for(int i = 0; i < sz(S); i++) { 
         int64_t ca = 0, cb = 0; 
         for(int j = i + 1; j < sz(S); j++) { 
            ca += pA[S[j] - 'a' + 1]; 
            cb += pB[S[j] - 'a' + 1]; 
            if(mp.count({ca, cb})) { 
               dyn[j] += dyn[i] % mod * mp[{ca, cb}] % mod; 
               dyn[j] %= mod; 
            }
         }
       }
       cout << dyn[sz(S) - 1] << " "; 
    }
    cout << '\n'; 
  }
  return 0; 
}