#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    vector<int> f(2 * n, -1);
    int ptr = 0;
    for (int i = 1; i < 2 * n; i++) {
        int j = f[i - ptr - 1]; 
        while(j != -1 && s[i % n] != s[(j + ptr + 1) % n]) {
            if(s[i % n] < s[(j + ptr + 1) % n]) {
                ptr = i - j - 1; 
            }
            j = f[j]; 
        }
        if(j == -1 && s[i % n] != s[(j + ptr + 1) % n]) { 
            if(s[i % n] < s[(j + ptr + 1) % n]) {
                ptr = i; 
            }
            f[i - ptr] = -1; 
        }
        else {
            f[i - ptr] = j + 1; 
        }
    }
    for (int i = 0; i < n; i++) cout << s[(i + ptr) % n];
    cout << '\n'; 
    return 0;
}