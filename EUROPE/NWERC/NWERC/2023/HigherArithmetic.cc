#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(0);  
    cin.tie(0); 
    int n; 
    cin >> n;
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    vector<vector<string>>p(2e6 + 1); 
    for(int i = 0; i < n; i++) { 
        p[a[i]].push_back(to_string(a[i])); 
    }
    auto merge = [&](int x, int y) { 
        string s = p[x].back();
        p[x].pop_back(); 
        string t = p[y].back(); 
        p[y].pop_back(); 
        p[x + y].push_back("(" + s + "+" + t + ")");
        return; 
    }; 
    while(sz(p[1])) { 
        if(sz(p[2])) { 
            merge(1, 2); 
        }
        else if(sz(p[1]) > 1) { 
            merge(1, 1); 
        }
        else if(n > 1) {
            int x = 2; 
            while(sz(p[x]) == 0) x++;
            merge(x, 1); 
        } 
        else break; 
    }
    int flag = false; 
    for(int i = 0; i < p.size(); i++) { 
        for(auto &v : p[i]) { 
            if(!flag) flag = true; 
            else cout << "*";
            cout << v; 
        }
    }
    cout << '\n'; 
    return 0; 
}