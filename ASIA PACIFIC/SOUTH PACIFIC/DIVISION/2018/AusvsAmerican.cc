#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n; 
    cin >> n;
    vector<int>state(6, true);  
    vector<int>month(100);
    month[1] = month[3] = month[5] = month[7] = month[8] = month[10] = month[12] = 31; 
    month[4] = month[6] = month[9] = month[11] = 30; 
    month[2] = 29;  
    for(int i = 0; i < n; i++) {
        string s; 
        cin >> s; 
        int a = (s[0] - '0') * 10 + s[1] - '0'; 
        int b = (s[3] - '0') * 10 + s[4] - '0'; 
        int c = (s[6] - '0') * 10 + s[7] - '0';
        state[0] &= (0 < a && a <= month[b]) & (0 < b && b <= 12) & (c <= 99);
        if(a == 29 & b == 2) state[0] &= (c % 4 == 0);  
        state[1] &= (0 < a && a <= month[c]) & (b <= 99) & (0 < c && c <= 12);
        if(a == 29 & c == 2) state[1] &= (b % 4 == 0);  
        state[2] &= (0 < a && a <= 12) & (0 < b && b <= month[a]) & (c <= 99); 
        if(a == 2 & b == 29) state[2] &= (c % 4 == 0);  
        state[3] &= (0 < a && a <= 12) & (b <= 99) & (0 < c && c <= month[a]);
        if(a == 2 & c == 29) state[3] &= (b % 4 == 0);  
        state[4] &= (a <= 99) & (0 < b && b <= 12) & (0 < c && c <= month[b]); 
        if(b == 2 & c == 29) state[4] &= (a % 4 == 0); 
        state[5] &= (a <= 99) & (0 < b && b <= month[c]) & (0 < c && c <= 12); 
        if(b == 29 & c == 2) state[5] &= (a % 4 == 0);  
    } 
    int ret = 0; 
    for(int i = 0; i < 6; i++) ret += state[i]; 
    if(ret > 1) { 
        cout << "UNSURE\n"; 
    }
    else if(ret == 1) { 
        if(state[0]) {  cout << "DD/MM/YY"; }
        if(state[1]) {  cout << "DD/YY/MM"; }
        if(state[2]) {  cout << "MM/DD/YY"; }
        if(state[3]) {  cout << "MM/YY/DD"; }
        if(state[4]) {  cout << "YY/MM/DD"; }
        if(state[5]) {  cout << "YY/DD/MM"; }
    }
    else { 
        cout << "IMPOSSIBLE\n"; 
    }
    return 0; 
} 