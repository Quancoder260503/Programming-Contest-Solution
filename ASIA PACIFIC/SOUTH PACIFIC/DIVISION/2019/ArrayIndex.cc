#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line, word;
    vector<map<int, int>>d(26);  
    while(getline(cin, line)) {
        stringstream ss(line); 
        vector<string>s;
        while(ss >> word) { 
            s.push_back(word); 
        }
        d[s[0][0] - 'A'][atoi(s[0].substr(2, sz(s[0]) - 2).c_str())] += atoi(s[2].c_str()); 
    }
    for(int i = 0; i < 26; i++) { 
        if(sz(d[i]) == 0) continue;
        cout << char('A' + i) << '\n';  
        for(const auto &[u, v] : d[i]) { 
            if(v == 0) continue; 
            cout << v << '\n'; 
        }
    }
    return 0; 
}