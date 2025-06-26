#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    string s; 
    cin >> s;
    vector<int>psum(sz(s) + 1); 
    pair<int, pair<int, int>>ret; 
    pair<int, int> opt = {0, 0}, opt2 = {0, 0}; 
    for(int i = 1; i < sz(s) + 1; i++) { 
        psum[i] = psum[i - 1] + (s[i - 1] == 'R'); 
        ret = max(ret, {i - 2 * psum[i] + opt.first,  {opt.second  - 1, -i}});
        ret = max(ret, {opt2.first - i + 2 * psum[i], {opt2.second - 1, -i}}); 
        opt2 = max(opt2, {i - 2 * psum[i], -i});
        opt  = max(opt,  {2 * psum[i] - i, -i});
    } 
    cout << -ret.second.first << " " << -ret.second.second << '\n'; 
    return 0; 
}
