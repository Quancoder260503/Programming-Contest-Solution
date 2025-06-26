
#include "bits/stdc++.h"

using namespace std;

const int maxf = 750;

int g[maxf][maxf];

int chk(int i, int j)
{
    return (i > 0 && j > 0 && i != j);
}

int doit(int i, int j)
{
    if (i > j)
        swap(i, j);
    if (g[i][j] != -1)
        return g[i][j];
    if (i == 1 && j == 2)
        return g[i][j] = 0;
    set<int> grundy;
    for (int k = 1; k <= j; k++)
    {
        if (k <= i && chk(i - k, j))
            grundy.insert(doit(i - k, j));
        if (k <= j && chk(i, j - k))
            grundy.insert(doit(i, j - k));
        if (k <= j && k <= i && chk(i - k, j - k))
            grundy.insert(doit(i - k, j - k));
    }
    int mex = 0;
    while (grundy.count(mex))
        mex++;
    return g[i][j] = mex;
}

int main(void)
{
    memset(g, -1, sizeof(g));
    int n;
    cin >> n;
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a == b)
        {
            cout << "Y\n";
            return 0; 
        }
        ret = ret ^ doit(a, b);
    }
    cout << (ret ? "Y" : "N") << '\n';
    return 0;
}