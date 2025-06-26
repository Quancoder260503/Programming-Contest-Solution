#include "bits/stdc++.h"
using namespace std;
struct lines
{
    int st, e;
    char type;
    lines(int _st, char _type, int _e) : st(_st), type(_type), e(_e){};
};
bool cmp(lines &a, lines &b)
{
    if (a.st != b.st)
        return a.st < b.st;
    if (a.e != b.e)
        return a.e < b.e;
    return a.type < b.type;
}
vector<lines> arr;
int n;
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char t;
        int x, y, len;
        cin >> t >> x >> len >> y;
        arr.push_back(lines(x - y, t, 1));
        arr.push_back(lines(x - y + len, t, -1));
    }
    sort(arr.begin(), arr.end(), cmp);
    long long ans = 0;
    long long cnt0 = 0, cnt2 = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].type == 'h')
        {
            cnt2 += arr[i].e;
            if(arr[i].e > 0)
            {
                ans += cnt0;
            }
        }
        else
        {
            cnt0 += arr[i].e;
            if(arr[i].e > 0)
            {
                ans += cnt2;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}