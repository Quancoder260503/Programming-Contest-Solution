#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

const int mod = 1e9 + 7; 

int main(void)
{
    string s;
    int n; 
    cin >> n >> s; 
    array<int64_t, 4>dyn = {1, 0, 0, 0}; 
    for(int i = 0; i < sz(s); i++) {
        array<int64_t, 4>ndyn = dyn;  
        if(s[i] == '?') {
            for(int j = 0; j <= 3; j++) ndyn[j] = ndyn[j] * 3 % mod; 
            for(int j = 0; j < 3;  j++) ndyn[j + 1] = (ndyn[j + 1] + dyn[j]) % mod; 
        }
        else {
            ndyn[s[i] - 'a' + 1] += dyn[s[i] - 'a']; 
            ndyn[s[i] - 'a' + 1] %= mod; 
        }
        dyn.swap(ndyn); 
    }
    cout << dyn[3] << '\n'; 
    return 0; 
}