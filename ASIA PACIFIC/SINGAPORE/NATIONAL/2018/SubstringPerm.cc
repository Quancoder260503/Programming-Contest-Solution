#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    string a, b; 
    cin >> a >> b;
    vector<int>ctra(26), ctrb(26); 
    for(int i = 0; i < a.size(); i++) ctra[a[i] - 'a']++; 
    for(int i = 0; i < b.size(); i++) ctrb[b[i] - 'a']++; 
    int ret = true; 
    for(int i = 0; i < 26; i++) ret &= (ctra[i] >= ctrb[i]); 
    cout << (ret ? "YES" : "NO") << '\n'; 
    return 0; 
}