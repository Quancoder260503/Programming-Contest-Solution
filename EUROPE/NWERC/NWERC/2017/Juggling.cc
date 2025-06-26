#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    vector<int> two;
    set<int> ms;
    int n = s.size(); 
    ms.insert(0);
    for (int i = 0; i < n; i++) {
        if (s[i] == '2') {
            two.push_back(i + 1);
        }
        if(s[i]  == '0') {
            ms.insert(i + 1); 
        }
    }
    if(two.empty()) {
        cout << s << '\n';
        return 0; 
    }
    ms.insert(n + 1);
    for (int i = 0; i < two.size(); i++) {
        auto l = --ms.lower_bound(two[i]);
        auto r = ms.lower_bound(two[i]);
        int at = (*l + *r - two[i]);
        if ((*l) != 0) ms.erase(*l);
        if ((*r) != n + 1) ms.erase(*r);
        ms.insert(at);
    }
    string ret(n, '1');
    for(auto x : ms) if (0 < x && x < n + 1) ret[x - 1] = '0';
    cout << ret << '\n'; 
    return 0;
}