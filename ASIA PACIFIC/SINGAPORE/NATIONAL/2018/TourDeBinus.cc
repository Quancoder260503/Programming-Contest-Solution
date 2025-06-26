#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> a(n), sum(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum[i] = (a[i] == 0);
    }
    int c;
    string s;
    cin >> c >> s;
    if (s == "left")
        cout << accumulate(a.begin(), a.begin() + c, 0LL) << " ";
    else
        cout << accumulate(a.begin() + c - 1, a.end(), 0LL) << " ";
    cin >> c >> s;
    if (s == "left")
        cout << accumulate(sum.begin(), sum.begin() + c, 0LL) << " ";
    else
        cout << accumulate(sum.begin() + c - 1, sum.end(), 0LL) << " ";
    return 0;
}