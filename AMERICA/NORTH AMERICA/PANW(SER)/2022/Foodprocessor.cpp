#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e5 + 10
int n;
long double s, t;
long double avg[MAXN], sec[MAXN];
bool cmp(const int a, const int b)
{
    return avg[a] == avg[b] ? sec[a] < sec[b] : avg[a] < avg[b];
}
signed main(void)
{
    cin >> s >> t >> n;
    long double curr = 0; 
    for (int i = 1; i <= n; i++)
    {
        cin >> avg[i] >> sec[i];
        curr = max(curr, avg[i]); 
    }
    if(curr < s)
    {
         puts("-1");
         return 0;
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), cmp);
    reverse(ord.begin(), ord.end());
    long double ans = 0;
    long double last = s;
    long double time = 1e9;
    for (int i = 0; i < ord.size(); i++)
    {
        int k = ord[i];
        if (avg[k] < t)
        {
            break;
        }
        if (avg[k] >= s)
        {
            time = min(time, sec[k]);
        }
        else
        {
            if (avg[k] < last)
            {
                ans += (long double) (log2(last / avg[k]) * time) ;
                last = avg[k];
            }
            time = min(time, sec[k]);
        }
    }
    ans += (long double) (log2(last / t) * time);
    cout << setprecision(20) << ans << '\n';  
    return 0;
}

/*
    sort the array descending by their maximum average size
    in the optimal answer
    dp[i] = min( dp[j] + log2(a[j] / a[i]) * t[j])
    Let k < j and i < k
    dp[k] + log2(a[k] / a[i]) * t[k] < dp[j] + log2(a[j] / a[i]) * t[j]
    dp[k] - dp[j] + log2(a[k]) * t[k] - log2(a[j]) * t[j] < log2(a[i]) * (log2(a[k]) - log2(a[j]))
    (dp[k] - dp[j] + log2(a[k]) * t[k] - log2(a[j]) * t[j]) / log2(a[k]) - log2(a[j]) < log2(a[i]); 
*/