#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    string s; 
    getline(cin, s);  
    map<char, string>mp; 
    mp['\t'] = " "; 
    mp['a'] = "@";  
    mp['b'] = "8"; 
    mp['c'] = "(";
    mp['d'] = "|)"; 
    mp['e'] = "3"; 
    mp['f'] = "#"; 
    mp['g'] = "6"; 
    mp['h'] = "[-]"; 
    mp['i'] = "|"; 
    mp['j'] = "_|";
    mp['k'] = "|<"; 
    mp['l'] = "1"; 
    mp['m'] = "[]\\/[]"; 
    mp['n'] = "[]\\[]"; 
    mp['o'] = "0"; 
    mp['p'] = "|D"; 
    mp['q'] = "(,)"; 
    mp['r'] = "|Z";
    mp['s'] = "$"; 
    mp['t'] = "']['"; 
    mp['u'] = "|_|";
    mp['v'] = "\\/"; 
    mp['w'] = "\\/\\/"; 
    mp['x'] = "}{"; 
    mp['y'] = "`/"; 
    mp['z'] = "2"; 
    for(int i = 0; i < s.size(); i++) { 
       if(mp.count(tolower(s[i]))) cout << mp[tolower(s[i])]; 
       else cout << s[i]; 
    }
    cout << '\n'; 
    return 0; 
}