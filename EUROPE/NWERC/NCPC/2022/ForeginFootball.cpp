#include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define MAXN 550
string g[MAXN][MAXN];
int n;
string s[N];
int len[N];
string A[N]; 
vector<int> kmp(string &s)
{
    int n = s.length();
    vector<int> pin(n);
    for (int i = 1, j = 0; i < n; i++)
    {
        while (j > 0 && s[i] != s[j])
            j = pin[j - 1];
        if (s[i] == s[j])
            j++;
        pin[i] = j;
    }
    return pin;
}
signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
        }
    }
    if (n == 2)
    {
        string a = g[1][2];
        string b = g[2][1];
        if (a.length() != b.length())
        {
            puts("NONE");
            return 0;
        }
        if (a == b && a.length() == 2)
        {
            if (a[0] != a[1])
                puts("NONE");
            else
            {
                puts("UNIQUE");
                cout << a[0] << '\n'
                     << a[1] << '\n';
            }
            return 0;
        }
        string c = a + '?' + b + b;
        vector<int> pi = kmp(c);
        string f, s;
        int cnt = 0;
        for (int i = a.length() + 1; i < pi.size(); i++)
        {
            if (a.length() == pi[i])
            {
                if(pi.size() == i + a.length() + 1) continue;
                if(pi.size() == i + 1) continue; 
                A[++cnt] = c.substr(i + 1, pi.size());
                if(cnt > 1) break; 
            }
        }
        if(cnt == 0)
        { 
            puts("NONE");
            return 0; 
        }
        if(cnt > 1)
        {
             puts("MANY");
             return 0; 
        }
        f = A[cnt]; 
        for (int i = f.size(); i < a.size(); i++)
        {
            s += a[i];
        }
        if (a == b && f == a)
        {
            puts("MANY");
        }
        else
        {
            puts("UNIQUE");
            cout << f << '\n'
                 << s << '\n';
        }
        return 0;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {

        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            len[i] += g[i][j].size();
            tot += g[i][j].size();
        }
    }
    tot = tot / 2;
    if (tot % (n - 1) != 0)
    {
        puts("NONE\n");
        return 0;
    }
    tot = tot / (n - 1);
    for (int i = 1; i <= n; i++)
    {
        if (len[i] <= tot)
        {
            puts("NONE");
            return 0;
        }
        if ((len[i] - tot) % (n - 2) != 0)
        {
            puts("NONE");
            return 0;
        }
        len[i] = (len[i] - tot) / (n - 2);
    }
    for (int i = 0; i < min(len[1], (int)g[1][2].length()); i++)
    {
        s[1] += g[1][2][i];
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = len[1]; j < g[1][i].length(); j++)
        {
            s[i] += g[1][i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            if (g[i][j] != s[i] + s[j])
            {
                puts("NONE");
                return 0;
            }
        }
    }
    puts("UNIQUE");
    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << '\n';
    }
    return 0;
}