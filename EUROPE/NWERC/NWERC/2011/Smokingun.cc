#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) (int)x.size()
#define x first
#define y second

const double INF = 1e100;

int main(void)
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m;
        cin >> n >> m;
        map<string, int> dict;
        vector<pair<int, int>> p(n);
        vector<string> s(n);
        for (int i = 0, x, y; i < n; i++)
        {
            cin >> s[i] >> p[i].x >> p[i].y;
            dict[s[i]] = i;
        }
        auto sqr = [&](int64_t x)
        { return 1LL * x * x; };
        auto dist = [&](int si, int sj)
        { return sqrt(sqr(p[si].x - p[sj].x) + sqr(p[si].y - p[sj].y)); };
        vector<vector<double>> dyn(n, vector<double>(n, INF));
        for(int i = 0; i < n; i++) dyn[i][i] = 0; 
        string line, word;
        cin.ignore();
        set<int> guns;
        for (int i = 0; i < m; i++)
        {
            getline(cin, line);
            stringstream ss(line);
            vector<string> cc;
            while (ss >> word) cc.push_back(word);
            int kk = dict[cc[0]], ii = dict[cc[2]], jj = dict[cc[5]];
            dyn[ii][jj] = min(dyn[ii][jj], dist(jj, kk) - dist(ii, kk));
            guns.insert(ii);
            guns.insert(jj);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    dyn[i][j] = min(dyn[i][j], dyn[i][k] + dyn[k][j]);
                }
        int sum = sz(guns);
        int f = true; 
        for (int i = 0; i < n; i++)
        {
            if (guns.count(i) && dyn[i][i] < 0)
            {
                f = false; 
            }
        }
        if(!f) {
            puts("IMPOSSIBLE"); 
            continue; 
        }
        vector<int> ret;
        while (sum--)
        {
            for (int i = 0; i < n; i++)
            {
                if (guns.count(i))
                {
                    f = true;
                    for (int j = 0; j < n; j++)if (i != j && guns.count(j) && dyn[i][j] >= 0){
                            f = false;
                            break;
                    }
                    if (f)
                    {
                        ret.push_back(i);
                        guns.erase(i);
                        break; 
                    }
                }
            }
            if (!f) break;
        }
        if(!f) puts("UNKNOWN");
        else { 
            for(auto idx : ret) cout << s[idx] << " "; 
            cout << '\n'; 
        }
    }
    return 0;
}