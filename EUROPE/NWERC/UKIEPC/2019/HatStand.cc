#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int c, n; 
    cin >> c >> n; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    vector<int>p(c + 1); 
    vector<pair<int, int>>s(c, {0, 0}); 
    for(int i = 0; i < c; i++) {
        s[i].second = i + 1; 
        p[i + 1] = i; 
    }
    for(int i = 1; i < n; i++) { 
        s[p[a[i]]].first++; 
        swap(p[a[i]], p[a[i - 1]]); 
    }
    s.erase(s.begin() + a[0] - 1); 
    sort(s.begin(), s.end()); 
    int64_t ret = 0; 
    for(int i = 0; i < sz(s); i++) { 
        ret += 1LL * (sz(s) - i) * s[i].first; 
    }
    cout << ret << '\n'; 
    reverse(s.begin(), s.end()); 
    for(int i = 0; i < sz(s); i++) { 
        cout << s[i].second << ' '; 
    }
    cout << '\n'; 
    return 0;
}