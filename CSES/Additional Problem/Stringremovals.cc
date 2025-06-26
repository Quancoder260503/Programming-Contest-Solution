#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7;
#define sz(x) (int) x.size()

int main(void) { 
    string s; 
    cin >> s;
    vector<int64_t>dyn(26);  
    for(int i = 0; i < sz(s); i++) { 
        dyn[s[i] - 'a']++; 
        for(int j = 0; j < 26; j++) if(j != s[i] - 'a') { 
            dyn[s[i] - 'a'] += dyn[j]; 
            dyn[s[i] - 'a'] %= mod; 
        }
    }
    int64_t ret = 0; 
    for(int i = 0; i < 26; i++) ret = (ret + dyn[i]) % mod; 
    cout << ret << '\n'; 
    return 0; 
}