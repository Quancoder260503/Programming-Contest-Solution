#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    string s;
    cin >> s; 
    vector<int>marked(4, false); 
    string c = "ACGT";
    int ctr = 0;  
    vector<int>cc; 
    for(int i = 0; i < s.size(); i++) { 
        if(!marked[c.find(s[i])]) { 
            marked[c.find(s[i])] = true; 
            ctr++; 
            if(ctr == 4) { 
                ctr = 0; 
                fill(marked.begin(), marked.end(), false); 
                cc.push_back(i); 
            }
        }
    } 
    for(int i = 0; i < cc.size(); i++) cout << s[cc[i]]; 
    for(int i = 0; i < 4; i++) if(!marked[i]) { 
        cout << c[i]; 
        break; 
    }
    cout << '\n'; 
    return 0; 
}