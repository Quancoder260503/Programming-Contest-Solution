#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int tc;
    cin >> tc;
    cin.ignore(); 
    string word, s; 
    while(tc--) { 
        getline(cin, s); 
        stringstream ss(s); 
        set<char>ms; 
        while(ss >> word) { 
            for(auto &x : word) ms.insert(tolower(x)); 
        }
        vector<char>ret; 
        for(char c = 'a'; c <= 'z'; c++) { 
            if(!ms.count(c)) ret.push_back(c); 
        }
        cout << (sz(ret) == 0 ? "pangram " : "missing "); 
        for(auto &x : ret) cout << x; 
        cout << '\n'; 
    } 
    return 0; 
}