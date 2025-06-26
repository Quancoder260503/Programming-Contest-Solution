#include "bits/stdc++.h"
using namespace std;
struct Matching
{
    int n;
    vector<vector<int>> ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;

    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0}
    {
    }

    void addEdge(int u, int v)
    {
        ke[u].push_back(v);
    }

    bool dfs(int u)
    {
        seen[u] = iteration;
        for (int v : ke[u])
        {
            if (matchR[v] < 0)
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u])
        {
            if (seen[matchR[v]] != iteration && dfs(matchR[v]))
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match()
    {
        int res = 0;
        int newMatches = 0;
        do
        {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++)
            {
                if (matchL[u] < 0 && dfs(u))
                    ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};
// }}}
int main(void)
{
    int N; 
    while(cin >> N)
    {
        map<int64_t, int>ctr; 
        int nodes = 0; 
        vector<pair<int, int>>edge; 
        vector<int64_t>ra(N), rb(N); 
        for(int i = 0; i < N; i++) 
        {
            cin >> ra[i] >> rb[i];
            int64_t a = ra[i], b = rb[i];  
            if(!ctr.count(a + b)) ctr[a + b] = nodes++;
            if(!ctr.count(a - b)) ctr[a - b] = nodes++; 
            if(!ctr.count(1LL * a * b)) ctr[1LL * a * b] = nodes++; 
            edge.push_back({i, ctr[a - b]}); 
            edge.push_back({i, ctr[a + b]}); 
            edge.push_back({i, ctr[1LL * a * b]}); 
        }
        Matching mbmc(nodes + N + 2); 
        for(auto [u, v] : edge) mbmc.addEdge(u, v); 
        if(mbmc.match() < N)
        {
            cout << "impossible" << '\n'; 
        }
        else 
        {
            for(int i = 0; i < N; i++) 
            {
                if(mbmc.matchL[i] == ctr[ra[i] + rb[i]])       cout << ra[i] << " + " << rb[i] << " = " << ra[i] + rb[i] << '\n'; 
                else if(mbmc.matchL[i] == ctr[ra[i] - rb[i]])       cout << ra[i] << " - " << rb[i] << " = " << ra[i] - rb[i] << '\n'; 
                else if(mbmc.matchL[i] == ctr[1LL * ra[i] * rb[i]]) cout << ra[i] << " * " << rb[i] << " = " << 1LL * ra[i] * rb[i] << '\n'; 
            }
        }
    }
    return 0; 
}