#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    using T = pair<string, pair<int, int>>; 
    vector<T>d(n);
    for(int i = 0; i < n; i++) { 
        string s; int a, b, c; 
        cin >> s >> a >> b >> c; 
        d[i] = {s, {a, a + b + c}}; 
    }
    sort(d.begin(), d.end(), [&](T a, T b) { 
        return a.second.second == b.second.second ? a.second.first < b.second.first : a.second.second < b.second.second; 
    });
    cout << d[0].first << '\n'; 
    return 0; 
}