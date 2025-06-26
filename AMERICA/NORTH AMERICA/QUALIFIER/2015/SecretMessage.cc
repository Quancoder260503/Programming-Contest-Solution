#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int tc;
    cin >> tc;
    while(tc--) { 
        string s; 
        cin >> s;
        int s_size;  
        for(s_size = 1; s_size * s_size < sz(s); s_size++); 
        string ret; 
        for(int i = 0; i < s_size; i++) { 
            string cc; 
            for(int j = i; j < sz(s); j += s_size) { 
                cc += s[j]; 
            }
            reverse(cc.begin(), cc.end()); 
            ret += cc; 
        }
        cout << ret << '\n'; 
    } 
    return 0; 
}