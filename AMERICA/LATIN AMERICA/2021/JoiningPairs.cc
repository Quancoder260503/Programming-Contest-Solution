#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int h, w, n; 
    cin >> w >> h >> n; 
    auto boundary = [&](int x, int y) {
        return (x == 0 || y == 0 || x == w || y == h); 
    }; 
    vector<pair<int, int>>L, R, U, D; 
    for(int i = 0; i < n; i++) { 
        int xa, xb, ya, yb;
        cin >> xa >> ya >> xb >> yb; 
        if(boundary(xa, ya) && boundary(xb, yb)) { 
            if(xa == 0) U.push_back({ya, i});
            else if (xa == w) D.push_back({ya, i});
            else if (ya == 0) L.push_back({xa, i});
            else if (ya == h) R.push_back({xa, i});
            if (xb == 0) U.push_back({ya, i});
            else if (xb == w) D.push_back({yb, i});
            else if (yb == 0) L.push_back({xb, i});
            else if (yb == h) R.push_back({xb, i});
        }
    }
    sort(L.rbegin(), L.rend());
    sort(D.rbegin(), D.rend());
    sort(U.begin(), U.end());
    sort(R.begin(), R.end());
    stack<int>stk; 
    vector<int>cc; 
    for(auto it : U)  cc.push_back(it.second); 
    for(auto it : R)  cc.push_back(it.second);
    for (auto it : D) cc.push_back(it.second);
    for (auto it : L) cc.push_back(it.second);
    for(int i = 0; i < cc.size(); i++) { 
        if(stk.size() && cc[i] == stk.top()) stk.pop(); 
        else stk.push(cc[i]); 
    }
    cout << (stk.size() ? "N" : "Y") << '\n'; 
    return 0; 
}