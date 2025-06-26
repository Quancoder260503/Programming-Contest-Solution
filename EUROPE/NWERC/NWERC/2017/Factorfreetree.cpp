#include "bits/stdc++.h"
using namespace std;
const int N = (int)1e6 + 10;
const int MAX = (int)1e7 + 1;
int n;
int arr[N], L[N], R[N];
int stkL[MAX], stkR[MAX];
vector<int> divisors[N];
int fa[N];
int Lprimes = 9999991;
int solve(int Left, int Right)
{
    if (Left >= Right)
    {
        return Left;
    }
    for (int l = Left, r = Right; l <= r; l++, r--)
    {
        int good = (L[l] < Left && Right < R[l]);
        if (good)
        {
            int sonL, sonR;
            if ((sonL = solve(Left, l - 1)) && (sonR = solve(l + 1, Right)))
            {
                fa[sonL] = fa[sonR] = l;
                return l;
            }
            else
            {
                return 0;
            }
        }
        good = (L[r] < Left && Right < R[r]);
        if (good)
        {
            int sonL, sonR;
            if ((sonL = solve(Left, r - 1)) && (sonR = solve(r + 1, Right)))
            {
                fa[sonL] = fa[sonR] = r;
                return r;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int num = arr[i];
        for (int j = 2; j * j <= num; j++)
        {
            if (num % j == 0)
            {
                L[i] = max(L[i], stkL[j]);
                stkL[j] = i;
            }
            while (num % j == 0)
                num = num / j;
        }
        if (num > 1)
        {
            L[i] = max(L[i], stkL[num]);
            stkL[num] = i;
        }
    }
    memset(R, 63, sizeof(R));
    memset(stkR, 63, sizeof(stkR));
    for (int i = n; i > 0; i--)
    {
        int num = arr[i];
        for (int j = 2; j * j <= num; j++)
        {
            if (num % j == 0)
            {
                R[i] = min(R[i], stkR[j]);
                stkR[j] = i;
            }
            while (num % j == 0)
                num = num / j;
        }
        if (num > 1)
        {
            R[i] = min(R[i], stkR[num]);
            stkR[num] = i;
        }
    }
    int ans = solve(1, n);
    if (ans)
    {
        fa[ans] = 0;
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", fa[i]);
        }
        printf("\n");
    }
    else
    {
        puts("impossible");
    }
    return 0;
}