#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 200 
vector<int>prob[10]; 
void solve()
{
    int n;
    cin >> n; 
    vector<int>b(n + 1), d(n + 1); 
    for(int i = 1; i <= 10; i++)
    {
         prob[i].clear(); 
    }
    for(int i = 1; i <= n; i++)
    {
         cin >> b[i] >> d[i];
         prob[d[i]].push_back(b[i]); 
    }
    bool good = 1; 
    for(int i = 1; i <= 10; i++)
    {
         sort(prob[i].begin(), prob[i].end());
         good = good & (prob[i].size() > 0); 
    }
    if(!good)
    {
        puts("MOREPROBLEMS"); 
    }
    else 
    {
        int sum = 0; 
        for(int i = 1; i <= 10; i++)
        {
            sum += prob[i].back(); 
        }
        cout << sum << endl; 
    }
}
signed main(void)
{
    int t; cin >> t; 
    for(int i = 1; i <= t; i++)
    {
         solve(); 
    }
    return 0;
}