#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    string s;
    cin >> s; 
    vector<int>ord(s.size());
    iota(ord.begin(), ord.end(), 0);
    stable_sort(ord.begin(), ord.end(), [&](int a, int b) { return s[a] < s[b]; }); 
    int ptr = ord[0];
    while(ptr) {
        ptr = ord[ptr];
        cout << s[ptr]; 
    } 
    cout << '\n'; 
    return 0; 
}