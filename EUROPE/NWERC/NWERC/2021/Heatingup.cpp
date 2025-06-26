#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
#define int unsigned long long
typedef pair<int, int> pii;
int n;
int a[N + 1];
bool f(int mid)
{
    vector<pair<int, int>> stk;
    long long val = mid;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (val >= a[i])
        {
            val += a[i];
            while (stk.size() && stk.back().first <= val)
            {
                val += stk.back().second;
                stk.pop_back();
            }
        }
        else
        {
            stk.push_back({a[i], val - mid + a[i]});
            val = mid;
        }
    }
    return !stk.size();
}
signed main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[n + i] = a[i];
    }
    int low = 0;
    int high = 1e13 + 10;
    while (low < high)
    {
        int mid = (high + low) / 2;
        if (f(mid))
            high = mid;
        else
            low = mid + 1;
    }
    cout << low << endl;
    return 0;
}