#include "bits/stdc++.h"
using namespace std;
const int64_t M = 1e12;
pair<int64_t, int64_t> crt(int64_t a1, int64_t m1, int64_t a2, int64_t m2)
{
    if (m1 < m2)
        swap(m1, m2), swap(a1, a2);
    if (m1 > M)
    {
        if (a1 % m2 == a2)
            return {a1, m1};
        return {-1, -1};
    }
    while (a1 % m2 != a2)
        a1 += m1;
    auto g = gcd(m1, m2);
    if (m1 / g > M / m2)
        return {a1 > M ? M + 1 : a1, M + 1};
    return {a1, m1 / g * m2};
}

vector<int> operator*(vector<int> &a, vector<int> &b)
{
    int N = a.size();
    vector<int> ret(N), p(N);
    for (int i = 0; i < N; i++)
        p[a[i]] = i;
    for (int i = 0; i < N; i++)
        ret[p[i]] = b[i];
    return ret;
}
void print(int64_t x)
{
    if(x > M) puts("huge"); 
    else cout << x << '\n'; 
} 
int main(void)
{
    int N;
    while (cin >> N)
    {
        vector<int> a(N), b(N);
        for (int i = 0; i < N; i++)
        {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < N; i++)
        {
            cin >> b[i];
            b[i]--;
        }
        auto ab = a * b;
        vector<int> vis(N);
        int64_t ret = 1;
        for (int i = 0; i < N; i++)
        {
            if (vis[i]) continue;
            int cyc = 0;
            int at = i;
            while (!vis[at])
            {
                cyc++;
                vis[at] = 1;
                at = ab[at];
            }
            ret = lcm(ret, 1LL* cyc); 
            if(abs(ret) > M)
            {
                ret = M; 
                break; 
            }
        }
        ret = ret * 2;
        fill(vis.begin(), vis.end(), 0);
        pair<int64_t, int64_t>res = {0, 1}; 
        vector<int>ar(N); 
        for(int i = 0; i < N; i++) ar[a[i]] = i; 
        for(int i = 0; i < N; i++) a[i] = ar[i]; 
        for (int i = 0; i < N; i++)
        {
            if (vis[i]) continue;
            int cyc = 0;
            int at = i;
            int offset = -1;
            int target = a[i];
            while (!vis[at])
            {
                if (at == target) offset = cyc;
                vis[at] = 1;
                cyc++;
                at = ab[at];
            }
            at = i;
            for (int k = 0; k < cyc; k++)
            {
                if (a[at] != target)
                {
                    offset = -1;
                    break;
                }
                at = ab[at];
                target = ab[target];
            }
            if (offset == -1)
            {
                print(ret); 
                goto done;
            }
            res = crt(res.first, res.second, offset, cyc); 
            if(res.second == -1)
            {
                print(ret);
                goto done;
            }
        }
        print(min(ret, 2 * res.first + 1));
    done:;
    }
    return 0;
}