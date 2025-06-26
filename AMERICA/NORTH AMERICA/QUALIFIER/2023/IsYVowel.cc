#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    string s; 
    cin >> s;
    vector<int>ret(2);  
    string vowel = "aeiou"; 
    for(int i = 0; i < s.size(); i++) { 
        if(vowel.find(s[i]) != -1) ret[0]++, ret[1]++; 
        if(s[i] == 'y') ret[1]++; 
    }
    cout << ret[0] << " " << ret[1] << '\n'; 
    return 0; 
}