#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N;
    vector<int>rx(N), ry(N); 
    map<pair<int, int>, int>mp;  
    for(int i = 0; i < N; i++) { 
        cin >> rx[i] >> ry[i]; 
        mp[{rx[i], ry[i]}]++; 
    }
    vector<pair<int, int>>dst = {{0, 2018}, {2018, 0}, {1118, 1680}, {1680, 1118}} ;
    int64_t ret = 0; 
    for(int i = 0; i < N; i++) {
        for(auto [x, y] : dst) {
            if(mp.count({rx[i] + x, ry[i] + y})) ret += mp[{rx[i] + x, ry[i] + y}]; 
            if(mp.count({rx[i] - x, ry[i] - y})) ret += mp[{rx[i] - x, ry[i] - y}]; 
            if(x == 0 || y == 0) continue; 
            if(mp.count({rx[i] + x, ry[i] - y})) ret += mp[{rx[i] + x, ry[i] - y}]; 
            if(mp.count({rx[i] - x, ry[i] + y})) ret += mp[{rx[i] - x, ry[i] + y}]; 
        }
    }
    ret = ret / 2; 
    cout << ret << '\n'; 
    return 0;
}