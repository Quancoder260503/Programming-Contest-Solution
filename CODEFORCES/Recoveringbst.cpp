#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)701
int tab[MAXN][MAXN];
int arr[MAXN];
int L[MAXN][MAXN];
int R[MAXN][MAXN];
int n;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
int solve(int root, int l, int r)
{
    if (l > r)
        return 0;
    if (l == r)
        return 1;
    if (L[root][l] != -1 && R[root][r] != -1)
        return L[root][l] & R[root][r];
    bool lef = (root == l);
    bool rig = (root == r);
    for (int i = l; i < root; i++)
    {
        if (tab[root][i] == 1)
            continue;
        lef = lef | solve(i, l, root - 1);
    }
    for (int i = root + 1; i <= r; i++)
    {
        if (tab[root][i] == 1)
            continue;
        rig = rig | solve(i, root + 1, r);
    }
    L[root][l] = lef;
    R[root][r] = rig;
    return (rig & lef);
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }
    sort(arr + 1, arr + n + 1);
    int good = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            tab[i][j] = gcd(arr[i], arr[j]);
        }
    }
    memset(L, -1, sizeof(L));
    memset(R, -1, sizeof(R)); 
    for (int i = 1; i <= n; i++)
    {
        good = good | solve(i, 1, n);
    }
    printf("%s\n", good ? "Yes" : "No");
    return 0;
}