#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int tc;
    cin >> tc;
    cin.ignore(); 
    while(tc--) { 
        string s; 
        getline(cin, s); 
        if(s.substr(0, 10) == "Simon says") { 
            cout << s.substr(11) << '\n'; 
        }
    } 
    return 0; 
}