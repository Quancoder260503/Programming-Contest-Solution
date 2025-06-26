#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int n, k;
    string s;
    cin >> n >> k >> s;
    string c(s.size(), '.'); 
    for (int i = 0; i < n; i++) {
        char start = (c[0] == '.' ? 'L' : c[0]);
        int flag = true; 
        for (int j = 0; j < n; j++) {
            if (c[j] == '.') { 
                if(s[j] == start) {
                    c[j] = start; 
                    start = (start == 'L' ? 'R' : 'L');
                }
                else {
                    c[j] = s[j];
                    flag = false;
                    break; 
                }
            } 
            else start = (c[j] == 'R' ? 'L' : 'R'); 
        }
        if (flag || k == 0) break;
        k--; 
    }
    cout << k << '\n'; 
    return 0;
}