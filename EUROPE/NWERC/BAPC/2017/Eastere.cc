#include "bits/stdc++.h"
using namespace std;
const int LOG = 21;
const int MAX = 5e5 + 10;
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, B, R;
    while (cin >> N >> R >> B)
    {
        vector<int64_t>rx(N), ry(N), bx(N), by(N); 
        for(int i = 0; i < R; i++) cin >> rx[i] >> ry[i]; 
        for(int i = 0; i < B; i++) cin >> bx[i] >> by[i]; 
        auto chk = [&](int64_t D)
        {
            Matching mbmc(B + R + 2); 
            for(int i = 0; i < R; i++) for(int j = 0; j < B; j++) if(1LL * (rx[i] - bx[j]) * (rx[i] - bx[j]) + 1LL * (ry[i] - by[j]) * (ry[i] - by[j]) < D)
            {
                mbmc.addEdge(i, j); 
            }
            return (B + R - mbmc.match()) >= N; 
        }; 
        int64_t L = 0; 
        int64_t R = 1e12; 
        while(L < R)
        {
            int64_t mid = (L + R + 1) / 2; 
            if(chk(mid)) L = mid;  
            else         R = mid - 1; 
        }
        cout << fixed << setprecision(10) << sqrt(L) << '\n'; 
    }
    return 0;
}
