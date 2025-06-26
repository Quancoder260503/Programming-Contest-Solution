#include "bits/stdc++.h"
using namespace std;
const int maxf = 350;
#define double long double 
int mod, N, M;
vector<int> prime;
void init(void)
{
    vector<bool> vis(maxf);
    prime.push_back(1);
    for (int i = 2; i < maxf; i++)
        if (!vis[i])
        {
            prime.push_back(i);
            for (int j = 2 * i; j < maxf; j += i)
                vis[j] = 1;
        }
    M = prime.size();
    return;
}
int main(void)
{
    init();
    int T; 
    cin >> T;
    while (T--)
    {
        cin >> N; 
        vector<vector<double>> dyn(M, vector<double>(N + 1, 0));
        vector<vector<pair<int, int>>>fa(M, vector<pair<int,int>>(N + 1, {-1, -1})); 
        for (int i = 1; i < M; i++) for (int j = 0; j <= N; j++)
        {
            int pp = prime[i];
            for (int k = 0; pp <= j; k++)
            {
                if(dyn[i][j] < dyn[i - 1][j - pp] + log10(pp))
                {
                    dyn[i][j] = dyn[i - 1][j - pp] + log10(pp); 
                    fa[i][j]  = {i - 1, j - pp}; 
                }
                pp = pp * prime[i];
            }
            if(dyn[i][j] < dyn[i - 1][j])
            {
                dyn[i][j] = dyn[i - 1][j]; 
                fa[i][j]  = fa[i - 1][j]; 
            }
        }
        int at  = M - 1;
        int rem = N; 
        pair<int, int>st = {-1, -1}; 
        vector<int>p; 
        int sum = 0; 
        while(fa[at][rem] != st)
        {
            auto [nat, nrem] = fa[at][rem];
            p.push_back(rem - nrem); 
            sum += rem - nrem;  
            at = nat; 
            rem = nrem; 
        } 
        while(rem--) p.push_back(1); 
        sort(p.begin(), p.end()); 
        vector<int>pi(N); 
        int ptr = 0; 
        for(int i = 0; i < p.size(); i++)
        {
            int cyclen = p[i];
            for(int k = ptr; k < ptr + cyclen - 1; k++)
            {
                pi[k] = k + 1; 
            }
            pi[ptr + cyclen - 1] = ptr; 
            ptr += cyclen; 
        }
        for(int i = 0; i < N; i++) cout << pi[i] + 1 << " "; 
        cout << '\n'; 
    }
    return 0;
}