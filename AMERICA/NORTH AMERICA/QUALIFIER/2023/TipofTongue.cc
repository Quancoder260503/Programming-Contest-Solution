#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7; 
const int maxf = 1e6 + 2; 

#define sz(x) (int) x.size()

map<int64_t, int>prefix[maxf], suffix[maxf]; 
map<pair<int64_t, int64_t>, int>mand[maxf]; 

int64_t pw[maxf]; 

int main(void)
{
    int n, q; 
    cin >> n >> q; 
    pw[0] = 1; 
    for(int i = 1; i < maxf; i++) pw[i] = pw[i - 1] * 37 % mod; 
    for(int i = 0; i < n; i++) { 
        string u; 
        cin >> u;
        int64_t h1 = 0, h2 = 0;  
        for(int j = 0; j < sz(u); j++)
        {
            h1 = (h1 + pw[j] * (u[j] - 'a' + 1) % mod) % mod; 
            h2 = (h2 + pw[j] * (u[sz(u) - j - 1] - 'a' + 1) % mod) % mod; 
            prefix[j][h1]++; 
            suffix[j][h2]++; 
            mand[j][{h1, h2}]++; 
        }
    }
    for(int i = 0; i < q; i++) { 
        string t, p, s; 
        cin >> t >> p >> s; 
        int64_t h1 = 0, h2 = 0; 
        reverse(s.begin(), s.end()); 
        for(int j = 0; j < sz(p); j++) h1 = (h1 + pw[j] * (p[j] - 'a' + 1) % mod) % mod;
        for(int j = 0; j < sz(s); j++) h2 = (h2 + pw[j] * (s[j] - 'a' + 1) % mod) % mod;  
        if(t == "AND") 
        {
            cout << mand[sz(p) - 1][{h1, h2}] << '\n'; 
        }
        else if(t == "OR")
        {
            cout << prefix[sz(p) - 1][h1] + suffix[sz(s) - 1][h2] - mand[sz(p) - 1][{h1, h2}] << '\n'; 
        }
        else
        {
            cout << prefix[sz(p) - 1][h1] + suffix[sz(s) - 1][h2] - 2 * mand[sz(p) - 1][{h1, h2}] << '\n'; 
        }
    }
    return 0;
}