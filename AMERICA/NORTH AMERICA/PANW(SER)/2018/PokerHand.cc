#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    map<char,int>c; 
    string S; 
    for(int i = 0; i < 5; i++) { 
        cin >> S; 
        c[S[0]]++; 
    }
    int mx = 0; 
    for(auto [x, y] : c) { 
        mx = max(mx, y); 
    }
    cout << mx << '\n'; 
    return 0; 
}