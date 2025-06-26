#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)3e5 + 10;
#define lint long long
int n, k;
int tin[MAXN], star[MAXN];
int dp[MAXN];
bool cmp(const int a, const int b)
{
    return star[a] == star[b] ? tin[a] < tin[b] : star[a] < star[b];
}
signed main(void)
{
    cin >> n >> k;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++)
    {
        cin >> tin[i] >> star[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), cmp);
    int at = 0;
    while (at < ord.size() && star[ord[at]] == 0)
    {
        pq.push(tin[ord[at]]);
        at++;
    }
    vector<int>res; 
    for(int i = at; i < ord.size(); i++)
    { 
        int preq = star[ord[i]];
        int curr = 0;  
        while(pq.size() && res.size() < preq)
        {
            res.push_back(pq.top()); 
            pq.pop(); 
        }
        if(res.size() == preq)
        {
            pq.push(tin[ord[i]]); 
        }
    }
    while(pq.size())
    {
        res.push_back(pq.top());
        pq.pop(); 
    }
    if(res.size() < k)
    {
        puts("IMPOSSIBLE"); 
    }
    else
    {
        lint ans = 0; 
        for(int i = 0; i < k; i++) ans += res[i];
        cout << ans << '\n'; 
    }
    return 0;
}