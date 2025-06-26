#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e5 + 10
int arr[MAXN];
int n, k;
int last[MAXN];
signed main(void)
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        last[arr[i]] = i;
    }
    vector<int> ans;
    set<int> s;
    for (int i = 1; i <= n; i++)
    {
        if (s.count(arr[i]))
            continue;
        if (ans.size())
        {
            while(ans.size() && last[ans.back()] > i && arr[i] < ans.back())
            {
                s.erase(ans.back());
                ans.pop_back();
            }
            ans.push_back(arr[i]);
            s.insert(arr[i]);
        }
        else
        {
            ans.push_back(arr[i]);
            s.insert(arr[i]);
        }
    }
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}