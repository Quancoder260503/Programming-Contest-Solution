#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7; 

struct suffix_array
{
    suffix_array(const vector<int> &VV) : N(VV.size())
    {
        vector<int> V(VV);
        init(V);
    }
    int N;
    vector<int> SA;
    vector<int> RA;

private:
    void compress(vector<int> &V, vector<int> &C)
    {
        copy(V.begin(), V.end(), C.begin());
        sort(C.begin(), C.end());
        auto cend = unique(C.begin(), C.end());
        for (int i = 0; i < N; i++)
        {
            V[i] = lower_bound(C.begin(), cend, V[i]) - C.begin() + 1;
        }
        V.push_back(0);
        C.push_back(0);
    }

    void compute_sa(vector<int> &V, vector<int> &C)
    {
        vector<int> T(N + 1);
        for (int i = 0; i <= N; i++)
            SA.push_back(i);
        for (int ski = 0; V[SA[N]] < N; ski = ski ? ski << 1 : 1)
        {
            fill(C.begin(), C.end(), 0);
            for (int i = 0; i < ski; i++)
                T[i] = N - i;
            for (int i = 0, p = ski; i <= N; i++)
                if (SA[i] >= ski)
                    T[p++] = SA[i] - ski;
            for (int i = 0; i <= N; i++)
                C[V[i]]++;
            for (int i = 1; i <= N; i++)
                C[i] += C[i - 1];
            for (int i = N; i >= 0; i--)
                SA[--C[V[T[i]]]] = T[i];

            T[SA[0]] = 0;
            for (int j = 1; j <= N; j++)
            {
                int a = SA[j];
                int b = SA[j - 1];
                T[a] = T[b] + (a + ski >= N || b + ski >= N ||
                               V[a] != V[b] || V[a + ski] != V[b + ski]);
            }
            V.swap(T);
        }
    }

    void init(vector<int> &V)
    {
        vector<int> OV(V);
        vector<int> C(N);
        compress(V, C);
        compute_sa(V, C);
        RA.resize(N + 1);
        for (int i = 0; i <= N; i++)
            RA[SA[i]] = i;
        return;
    }
};

const int maxw = 301;

int main(void)
{
    int n;
    cin >> n;
    vector<int> sz(n), cc;
    for (int i = 0; i < n; i++)
    {
        cin >> sz[i];
        for (int j = 0, x; j < sz[i]; j++)
        {
            cin >> x;
            cc.push_back(x);
        }
        cc.push_back(maxw);
    }
    suffix_array sa(cc);
    set<pair<int, int>> s;
    int ptr = 0;
    for (int i = 0; i < n; i++)
    {
        s.insert({sa.RA[ptr], ptr});
        ptr += sz[i] + 1;
    }
    vector<int>ret;
    for(int i = 0; i < cc.size() - n; i++) { 
        int curr = (*s.begin()).second; 
        ret.push_back(cc[curr]); 
        s.erase(s.begin()); 
        s.insert({sa.RA[curr + 1], curr + 1}); 
    }
    int64_t res = 0, mul = 1; 
    reverse(ret.begin(), ret.end()); 
    for(auto c : ret) { 
        mul = mul * 365 % mod;
        res = (res + mul * c % mod) % mod;
    }
    cout << res << '\n'; 
    return 0;
}