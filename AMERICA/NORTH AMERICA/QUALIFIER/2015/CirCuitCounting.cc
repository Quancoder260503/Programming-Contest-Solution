#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define x first
#define y second

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int tc, n;
    tc = 1; 
    while(tc--) { 
        cin >> n; 
        map<pair<int, int>, int>ms; 
        int L = n / 2, R = n - L; 
        vector<pair<int, int>>pts(n); 
        for(int i = 0; i < n; i++) { 
            cin >> pts[i].x >> pts[i].y; 
        }
        for(int mask = 0; mask < (1 << L); mask++) {
            pair<int, int>sum = {0, 0}; 
            for(int i = 0; i < L; i++) if(mask & (1 << i)) { 
                sum.x += pts[i].x; 
                sum.y += pts[i].y; 
            }
            ms[sum]++; 
        }
        int64_t ret = 0; 
        for(int mask = 0; mask < (1 << R); mask++) { 
            pair<int, int>sum = {0, 0}; 
            for(int i = 0; i < R; i++) if(mask & (1 << i)) { 
                sum.x += pts[L + i].x;
                sum.y += pts[L + i].y; 
            }
            sum.x = -sum.x, sum.y = -sum.y; 
            ret += ms[sum]; 
        }
        ret--; 
        cout << ret << '\n'; 
    } 
    return 0; 
}