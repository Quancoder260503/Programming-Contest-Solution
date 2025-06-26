#include "bits/stdc++.h"
using namespace std;
#define double long double
const int N = 2e5 + 10;
int n;
double H[N], X[N];
double ans[N];
const double PI = acos(-1);
double get_angle(int i, int j)
{
    if (H[i] >= H[j]) return PI / 2.0;
    return atan(1.0 * fabs(X[i] - X[j]) / (1.0 * H[j] - H[i]));
}
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> X[i] >> H[i];
    }
    vector<int> stk;
    for (int i = 0; i < n; i++)
    {
        while (stk.size() > 1 && get_angle(i, stk[stk.size() - 2]) <= get_angle(i, stk.back()))
        {
            stk.pop_back();
        }
        ans[i] += (stk.size() ? get_angle(i, stk.back()) : PI / 2.0);
        stk.push_back(i);
    }
    while (stk.size()) stk.pop_back();
    for (int i = n - 1; i >= 0; i--)
    {
        while (stk.size() > 1 && get_angle(i, stk[stk.size() - 2]) <= get_angle(i, stk.back()))
        {
            stk.pop_back();
        }
        ans[i] += (stk.size() ? get_angle(i, stk.back()) : PI / 2.0);
        stk.push_back(i);
    }
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(10) << (ans[i] / PI) * 12.0 << '\n';
    }
    return 0;
}