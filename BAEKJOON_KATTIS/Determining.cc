#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

struct AhoCorasick
{
    enum
    {
        alpha = 26,
        first = 'a'
    }; // change this!
    struct Node
    {
        // (nmatches is optional)
        int back, next[alpha], start = -1, end = -1, nmatches = 0;
        Node(int v) { memset(next, v, sizeof(next)); }
    };
    vector<Node> N;
    vector<int> backp;
    void insert(string &s, int j)
    {
        assert(!s.empty());
        int n = 0;
        for (char c : s)
        {
            int &m = N[n].next[c - first];
            if (m == -1)
            {
                n = m = sz(N);
                N.emplace_back(-1);
            }
            else n = m;
        }
        if (N[n].end == -1) N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }
    AhoCorasick(vector<string> &pat) : N(1, -1)
    {
        for (int i = 0; i < sz(pat); i++) insert(pat[i], i);
        N[0].back = sz(N);
        N.emplace_back(0);
        queue<int> q;
        for (q.push(0); !q.empty(); q.pop())
        {
            int n = q.front(), prev = N[n].back;
            for (int i = 0; i < alpha; i++)
            {
                int &ed = N[n].next[i], y = N[prev].next[i];
                if (ed == -1)
                    ed = y;
                else
                {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    q.push(ed);
                }
            }
        }
    }
    vector<int> find(string word)
    {
        int n = 0;
        vector<int> res; // ll count = 0;
        for (char c : word)
        {
            n = N[n].next[c - first];
            res.push_back(N[n].end);
            // count += N[n].nmatches;
        }
        return res;
    }
    vector<vector<int>> findAll(vector<string> &pat, string word)
    {
        vector<int> r = find(word);
        vector<vector<int>> res(sz(word));
        for (int i = 0; i < sz(word); i++)
        {
            int ind = r[i];
            while (ind != -1)
            {
                res[i - sz(pat[ind]) + 1].push_back(ind);
                ind = backp[ind];
            }
        }
        return res;
    }
};

int main(void)
{
    int N, Q;
    cin >> N;
    vector<string> pat(N);
    for (int i = 0; i < N; i++)
    {
        cin >> pat[i];
    }
    AhoCorasick aho(pat);
    cin >> Q; 
    for(int i = 0; i < Q; i++)
    {
        string W; 
        cin >> W; 
        auto ret = aho.find(W); 
        int res = 0; 
        for(auto it : ret) res = res || (it != -1); 
        cout << (res ? "YES" : "NO") << '\n'; 
    }
    return 0;
}
