#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e6 + 10; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    for(int i = n + 1; i < maxf; i++) {
        string s = to_string(i); 
        if(s.find('0') == -1) { 
            cout << s << '\n';
            exit(0); 
        }
    } 
    return 0; 
}