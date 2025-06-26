#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int) 2e5 + 10;
int arr[MAXN];
int n, K;
bool f(int d)
{
    map<int, int> dp;
    for (int i = 1; i <= d; i++)
    {
        dp[arr[i]]++;
    }
    int good = (dp.size() == K);
    for (int i = d + 1; i <= n; i++)
    {
        dp[arr[i - d]]--;
        if (dp[arr[i - d]] == 0) dp.erase(arr[i - d]);
        dp[arr[i]]++;
        good = good & (dp.size() == K);
    }
    return good;
}
signed main(void)
{
    cin >> n; 
    set<int>s;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i]; 
        s.insert(arr[i]);
    }
    K = s.size(); 
    int lo = 1;
    int hi = n; 
    while(lo < hi)
    {
        int mid = (lo + hi) / 2; 
        if(f(mid))
        {
            hi = mid; 
        }
        else 
        {
            lo = mid + 1; 
        }
    }
    cout << lo << '\n';
    return 0;
}