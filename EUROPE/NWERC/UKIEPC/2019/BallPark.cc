#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int64_t INF = 1e14; 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    string s; 
    cin >> s; 
    int64_t n = stoll(s); 
    for(int i = 1; i < s.size(); i++) s[i] = '0'; 
    int64_t a = stoll(s); 
    int64_t p = 1; 
    for(int i = 0; i < s.size() - 1; i++) p = p * 10; 
    int64_t b = a + p; 
    if(a + b <= 2 * n) { 
        cout << b << '\n'; 
    }
    else { 
        cout << a << '\n'; 
    }
    return 0; 
}