#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    string s; 
    cin >> s; 
    vector<int>ctr(2); 
    for(int i = 0; i < s.size(); i++) { 
        ctr[s[i] - '0']++; 
    }
    if(ctr[0] == ctr[1]) { 
        string ret(1, (s[0] == '0' ? '1' : '0')); 
        for(int i = 1; i < s.size(); i++) ret += s[0]; 
        cout << ret << '\n'; 
    }
    else if(ctr[0] > ctr[1]) { 
        string ret(s.size(), '1'); 
        cout << ret << '\n'; 
    }
    else {
        string ret(s.size(), '0');
        cout << ret << '\n';
    }
    return 0; 
}

