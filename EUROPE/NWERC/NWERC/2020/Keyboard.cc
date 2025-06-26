#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    string a, b; 
    getline(cin, a); 
    getline(cin, b);
    vector<int>ca(256), cb(256); 
    for(int i = 0; i < a.size(); i++) ca[a[i]]++; 
    for(int i = 0; i < b.size(); i++) cb[b[i]]++; 
    for(int i = 0; i < 256; i++) { 
        if(ca[i] != cb[i]) cout << char(i); 
    }
    cout << '\n'; 
    return 0; 
}