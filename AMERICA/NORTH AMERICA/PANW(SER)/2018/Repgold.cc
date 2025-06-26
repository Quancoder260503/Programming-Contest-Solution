#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1e6 + 1; 
const int INF = 1e9; 
int dyn[MAXN]; 
int vis[MAXN]; 
int L, R; 
int memo(int num)
{
    if(num == 4) return 1;
    if(num <  4) return 0; 
    for(int i = 3; i <= num; i++)
    {
        if(!vis[i] && !vis[num - i]) return (1 + memo(abs(num - 2 * i))); 
    }
    return INF; 
}; 
signed main(void)
{
    for(int i = 2; i < MAXN; i++)
    {
        if(vis[i]) continue; 
        for(int j = 2 * i; j < MAXN; j += i) vis[j] = 1; 
    }
    int N; 
    while(cin >> N)
    {
        cout << memo(N) << '\n'; 
    }
    return 0;
}