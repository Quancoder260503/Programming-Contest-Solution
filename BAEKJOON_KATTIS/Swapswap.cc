#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N, M, K; 
    while(cin >> N >> M >> K)
    {
        vector<int>perm(N); 
        iota(perm.begin(), perm.end(), 0); 
        for(int i = 0; i < M; i++)
        {
            int L, R; 
            cin >> L >> R; 
            reverse(perm.begin() + L - 1, perm.begin() + R); 
        }
        vector<int>vis(N); 
        vector<int>ret(N); 
        for(int i = 0; i < N; i++) if(!vis[i])
        {
            int at = i; 
            int cyc = 0; 
            while(!vis[at])
            {
                cyc++; 
                vis[at] = 1; 
                at = perm[at]; 
            }
            int steps = K % cyc; 
            at = i; 
            for(int i = 0; i < steps; i++) 
            {
                at = perm[at]; 
            }
            int target = at; 
            at = i; 
            for(int i = 0; i < cyc; i++)
            {
                ret[at] = target; 
                at = perm[at];
                target = perm[target]; 
            }
        }
        for(int i = 0; i < N; i++) cout << ret[i] + 1 << '\n'; 
    }
    return 0; 
}