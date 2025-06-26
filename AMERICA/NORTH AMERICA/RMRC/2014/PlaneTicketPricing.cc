#include "bits/stdc++.h"

using namespace std; 

const int N = 5000; 

int dyn[N][N], n, m; 
vector<vector<pair<int,int>>>price; 
vector<pair<int, int>>res;

int memo(int seat, int week) { 
    if(week == m || seat == 0) return 0;
    int &ret = dyn[seat][week];  
    if(ret != -1) return ret; 
    ret = 0; 
    for(int i = 0; i < price[week].size(); i++) { 
        auto [nprice, nseat] = price[week][i]; 
        if(nseat <= seat) { 
            ret = max(ret, nseat * nprice + memo(seat - nseat, week + 1)); 
            if(!week) res.push_back({nseat * nprice + memo(seat - nseat, week + 1), -nprice}); 
        }
        else { 
            ret = max(ret, seat * nprice);
            if(!week) res.push_back({seat * nprice, -nprice}); 
        } 
    }
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);   
    cin >> n >> m; 
    ++m; 
    price.resize(m); 
    for(int i = 0, x; i < m; i++) { 
        cin >> x; 
        price[i].resize(x); 
        for(int j = 0; j < x; j++) { 
            cin >> price[i][j].first; 
        }
        for(int j = 0; j < x; j++) { 
            cin >> price[i][j].second; 
        }
    }
    memset(dyn, -1, sizeof(dyn)); 
    cout << memo(n, 0) << '\n'; 
    sort(res.rbegin(), res.rend()); 
    cout << -res[0].second << '\n'; 
    return 0; 
}