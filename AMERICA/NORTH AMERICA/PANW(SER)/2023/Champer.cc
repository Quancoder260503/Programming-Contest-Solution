#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    vector<string>ss = {"1", "12", "123", "1234", "12345", "123456", "1234567", "12345678", "123456789"}; 
    string s; 
    cin >> s; 
    for(int i = 0; i < ss.size(); i++) if(ss[i] == s) { 
        cout << i + 1 << '\n'; 
        return 0; 
    }
    cout << -1 << '\n'; 
    return 0; 
}