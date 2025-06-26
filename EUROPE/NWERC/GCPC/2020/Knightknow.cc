#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int M, C;
    map<int, int>rx, ry, rxc, ryc; 
    set<pair<int, int>>s; 
    cin >> M >> C; 
    for(int i = 0; i < M; i++)
    {
        int x, y; 
        cin >> x >> y; 
        rx[x]++, ry[y]++; 
    }
    for(int i = 0; i < C; i++)
    {
        int x, y; 
        cin >> x >> y; 
        if(rx.count(x) && rx[x] >= 2) continue; 
        if(ry.count(y) && ry[y] >= 2) continue; 
        rxc[x]++, ryc[y]++; 
        s.insert({x, y}); 
    }
    int ret = 0; 
    pair<int, int>res;
    for(auto x : rxc) for(auto y : ryc)
    {
        int ctr = 0; 
        if(rx.count(x.first))
        {
            ctr += x.second; 
        }
        if(ry.count(y.first))
        {
            ctr += y.second; 
        }
        if(rx.count(x.first) && ry.count(y.first))
        {
            ctr -= s.count({x.first, y.first}); 
        }
        if(ctr > ret)
        {
            ret = ctr;
            res.first  = x.first;
            res.second = y.first; 
        }
    }
    cout << res.first << " " << res.second << '\n'; 
    cout << ret << '\n'; 
    return 0; 
}