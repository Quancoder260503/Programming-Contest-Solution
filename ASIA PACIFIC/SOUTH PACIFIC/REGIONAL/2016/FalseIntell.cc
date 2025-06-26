#include "bits/stdc++.h"

using namespace std;

string AND(string a, string b)
{
    string ret(9, ' ');
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == 'U' && b[i] == 'U')
        {
            ret[i] = 'U';
            continue;
        }
        if (a[i] == 'T' && b[i] == 'U')
        {
            ret[i] = 'U';
            continue;
        }
        if (a[i] == 'U' && b[i] == 'T')
        {
            ret[i] = 'U';
            continue;
        }
        ret[i] = (a[i] == 'F' || b[i] == 'F' ? 'F' : 'T');
    }
    return ret;
}

string OR(string a, string b)
{
    string ret(9, ' ');
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == 'U' && b[i] == 'U')
        {
            ret[i] = 'U';
            continue;
        }
        if (a[i] == 'F' && b[i] == 'U')
        {
            ret[i] = 'U';
            continue;
        }
        if (a[i] == 'U' && b[i] == 'F')
        {
            ret[i] = 'U';
            continue;
        }
        ret[i] = (a[i] == 'T' || b[i] == 'T' ? 'T' : 'F');
    }
    return ret;
}

string IMPLIES(string a, string b)
{
    string ret(9, ' ');
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == 'F' || b[i] == 'T' || a[i] == b[i])
        {
            ret[i] = 'T';
            continue;
        }
        if (a[i] == 'U' || b[i] == 'U')
        {
            ret[i] = 'U';
            continue;
        }
        ret[i] = 'F';
    }
    return ret;
}
string EQUAL(string a, string b)
{
    string ret(9, ' ');
    for (int i = 0; i < 9; i++)
    {
        ret[i] = (a[i] == b[i] ? 'T' : 'F');
    }
    return ret;
}

map<string, int> dist;

void init(void)
{
    queue<string> q;
    string x = "FFFUUUTTT";
    string y = "FUTFUTFUT";
    q.push(x);
    q.push(y);
    dist[x] = dist[y] = 0;
    vector<string> vis;
    while (q.size())
    {
        string u = q.front();
        q.pop();
        vis.push_back(u);
        for (auto x : vis)
        {
            for (int i = 0; i < 2; i++)
            {
                for (auto f : {AND, OR, IMPLIES, EQUAL})
                {
                    auto v = f(u, x);
                    if (!dist.count(v))
                    {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
                swap(u, x);
            }
        }
    }
    return;
}

int main(void)
{
    init();
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string query;
        for (int k = 0; k < 9; k++)
        {
            char c;
            cin >> c;
            query += c;
        }
        cout << (dist.count(query) ? "" : "un") << "definable" << '\n';
    }
    return 0;
}