#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e6 + 10;
int n, thres;
int arr[MAXN];
signed main(void)
{
    scanf("%d %d", &n, &thres);
    for (int i = 0; i < (1 << n); i++)
    {
        scanf("%d", &arr[i]);
    }
    if(thres > *max_element(arr, arr + (1 << n)))
    {
        cout << (1 << n) - 1 << endl;
        return 0;
    }
    sort(arr, arr + (1 << n));
    reverse(arr, arr + (1 << n));
    vector<int> now;
    now.push_back(arr[0]);
    now.push_back(arr[1]);
    int ans = (arr[0] - arr[1] <= thres);
    for (int i = 1; i < n; i++)
    {
        vector<int> match;
        for (int j = (1 << i) - 1; j >= 0; j--)
        {
            match.push_back(arr[now.size() + j]);
        }
        for (int j = now.size() - 1; j >= 0; j--)
        {
            auto it = upper_bound(match.begin(), match.end(), now[j] - thres - 1);
            int at = it - match.begin();
            if (it == match.end()) break;
            ans += (now[j] - match[at] <= thres);
            match.erase(it);
        }
        int N = now.size();
        for (int j = 0; j < (1 << i); j++)
        {
            now.push_back(arr[N + j]);
        }
    }
    cout << ans << endl;
    return 0;
}