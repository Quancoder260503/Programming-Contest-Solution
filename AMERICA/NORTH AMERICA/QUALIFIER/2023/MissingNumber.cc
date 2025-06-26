#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int U = 99999; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int tc; 
    cin >> tc; 
    while(tc--) { 
        string s;
        cin >> s;
        set<int>ms;  
        for(int i = 1; i <= min(sz(s), 5); i++) { 
            ms.insert(stoi(s.substr(0, i)));
            ms.insert(stoi(s.substr(0, i)) - 1); 
        }
        vector<int>ret; 
        for(auto &x : ms) { 
            if(x <= 0) continue; 
            int cid = 0; 
            for(int skip = x; skip <= U; skip++) { 
                int flag = true, id = cid; 
                for(int i = skip + 1; flag; i++) { 
                    if(id == sz(s)) break; 
                    if(i > U) { 
                        flag = false; 
                        break; 
                    }
                    if(id + sz(to_string(i)) > sz(s)) { 
                        flag = false;
                        break; 
                    }
                    if(s.substr(id, sz(to_string(i))) != to_string(i)) { 
                        flag = false;
                        break; 
                    }
                    id += sz(to_string(i)); 
                }
                if(flag) ret.push_back(skip);
                if(cid + sz(to_string(skip)) > sz(s)) break; 
                if(s.substr(cid, sz(to_string(skip))) != to_string(skip)) break;
                cid += sz(to_string(skip)); 
            }
        }
        sort(ret.begin(), ret.end()); 
        ret.erase(unique(ret.begin(), ret.end()), ret.end()); 
        cout << sz(ret) << '\n'; 
        for(auto &x : ret) cout << x << ' ';
        cout << '\n';  
    }
    return 0; 
}