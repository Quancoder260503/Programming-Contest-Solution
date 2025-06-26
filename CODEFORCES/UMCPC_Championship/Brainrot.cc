#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class Brainrot { 
  public:   
   const string a = "shikanokonokonokoshitantan"; 
   const string b = "brrskibididopdopyesyesshtibididipdipww"; 
   void solve() { 
    int N; 
    string S; 
    cin >> N >> S;
    vector<int>freq_a(26, 0), freq_b(26, 0), freq(26, 0); 
    for(int i = 0; i < sz(a); i++) { 
      freq_a[a[i] - 'a']++; 
    } 
    for(int i = 0; i < sz(b); i++) { 
      freq_b[b[i] - 'a']++;  
    }
    for(int i = 0; i < sz(S); i++) { 
      freq[S[i] - 'a']++; 
    }
    int cc = 1000000; 
    for(int i = 0; i < 26; i++) { 
     if(freq_a[i] == 0) continue;
     cc = min(cc, freq[i] / freq_a[i]);  
    }
    int ans = 0;
    for(int j = 0; j <= cc; j++) { 
     vector<int>freq_rem(freq.begin(), freq.end()); 
     for(int i = 0; i < 26; i++) { 
      freq_rem[i] -= j * freq_a[i];
     }
     int cnt = 1000000;  
     for(int i = 0; i < 26; i++) { 
      if(freq_b[i] == 0) continue; 
      cnt = min(cnt, freq_rem[i] / freq_b[i]); 
     }
     if(cnt == 1000000) cnt = 0; 
     ans = max(ans, j + cnt); 
    }
    cout << ans << '\n'; 
    return; 
   } 
};


int main(void) {  
 Brainrot problem; 
 problem.solve(); 
 return 0; 
}