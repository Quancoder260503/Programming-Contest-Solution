#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    string s; 
    cin >> s; 
    reverse(s.begin(), s.end());
    string ret; 
    for(int i = 0; i < s.size(); i++) {
        ret = ret + s[i] + s[i] + s[i]; 
    } 
    cout << ret << '\n'; 
    return 0; 
}