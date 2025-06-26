#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 2;

vector<string> g[maxf];
vector<string> ret[maxf];
set<pair<int, string>> pool;

int main(void)
{
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            string c;
            cin >> c;
            g[i].push_back(c);
        }
        reverse(g[i].begin(), g[i].end());
    }
    int Q;
    cin >> Q;
    map<string, int>ctr;
    for (int i = 0; i < Q; i++)
    {
        string c;
        cin >> c;
        ctr[c] = i; 
        pool.insert({i, c});
    }
    for (int _ = 0; _ < K; _++)
    {
        for (int i = 0; i < N; i++)
        {
            bool flag = 0;
            while (g[i].size() && pool.find({ctr[g[i].back()], g[i].back()}) == pool.end())
            {
                g[i].pop_back();

            }
            if(g[i].size())
            {
                ret[i].push_back(g[i].back());
                pool.erase({ctr[g[i].back()], g[i].back()}); 
            }
            else 
            {
                ret[i].push_back(pool.begin() -> second); 
                pool.erase(pool.begin()); 
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (auto v : ret[i])
            cout << v << " ";
        cout << '\n';
    }
    return 0;
}