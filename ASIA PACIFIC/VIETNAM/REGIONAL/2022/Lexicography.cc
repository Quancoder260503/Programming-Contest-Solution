#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  int N, K, T; 
  for(cin >> T; T--; ) { 
   string S; 
   cin >> S >> K;
   N = sz(S); 
   vector<int>freq(26); 
   for(int i = 0; i < N; i++) { 
    freq[S[i] - 'a']++; 
   }
   int rem = N; 
   auto can_go = [&]()  {
     int c = *max_element(freq.begin(), freq.end());
     return c <= 1LL * (rem - c + 1) * (K - 1); 
   };
   if(!can_go()) { 
    cout << "OH NO!\n"; 
    continue; 
   }   
   string ret = ""; 
   vector<int>last(26, 0); 
   for(int pos = 0; pos < N; pos++) { 
    for(int i = 0; i < 26; i++) { 
     if(freq[i] > 0 && last[i] < K - 1) { 
      freq[i]--; 
      rem--; 
      if(can_go()) { 
        ret += char(i + 'a'); 
        last[i]++; 
        for(int j = 0; j < 26; j++) { 
         if(j != i) last[j] = 0; 
        }
        break; 
      }
      freq[i]++;
      rem++;  
     }
    }
   }
   cout << ret << '\n'; 
done:; 
  }
  return 0; 
}