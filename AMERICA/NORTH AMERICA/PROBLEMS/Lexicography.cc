#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = LLONG_MAX / 2;
const int maxf = 102;

int64_t fact[maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    fact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i] = fact[i - 1] * i;
        if(fact[i] > oo / i) break;
    }
    int tc; 
    string S; 
    int64_t K; 
    while(cin >> S >> K) { 
        if(S == "#") break; 
        vector<int>ctr(26); 
        for(int i = 0; i < S.size(); i++) {
            ctr[S[i] - 'A']++;  
        }
        string ret; 
        K--;
        for(int pos = 0; pos < sz(S); pos++) { 
            for(int c = 0; c < 26; c++) { 
                if(ctr[c] == 0) continue; 
                int64_t ways = fact[sz(S) - pos - 1];
                ctr[c]--;  
                for(int j = 0; j < 26; j++) { 
                    ways = ways / fact[ctr[j]]; 
                }
                if(K >= ways) { 
                    K = K - ways; 
                    ctr[c]++; 
                }
                else { 
                    ret += char(c + 'A'); 
                    break; 
                }
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}