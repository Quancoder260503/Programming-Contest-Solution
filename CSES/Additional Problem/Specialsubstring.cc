#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

map<vector<int>, int64_t>dyn; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    string s; 
    cin >> s; 
    map<char, int>c; 
    int nodes = 0; 
    for(int i = 0; i < sz(s); i++) { 
        if(!c.count(s[i])) c[s[i]] = nodes++;
    }
    int m = sz(c);
    vector<int>freq(m, 0); 
    int64_t ret = 0; 
    auto chk = [&](vector<int>cc) { 
        for(int i = 0; i < sz(cc); i++) { 
            if(cc[i] <= 0) return false; 
        }
        return true;  
    }; 
    dyn[freq] = 1; 
    for(int i = 0; i < sz(s); i++) { 
        freq[c[s[i]]]++;
        if(chk(freq)) { 
            for(int j = 0; j < sz(freq); j++) freq[j]--; 
        }
        ret += dyn[freq];
        dyn[freq]++;
    }
    cout << ret << '\n'; 
    return 0;
}