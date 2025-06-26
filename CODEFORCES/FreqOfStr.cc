#include "bits/stdc++.h"

using namespace std;

#define sz(x) x.size()

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
            else
                n = m;
        }
        if (N[n].end == -1)
            N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }
    AhoCorasick(vector<string> &pat) : N(1, -1)
    {
        for (int i = 0; i < sz(pat); i++)
            insert(pat[i], i);
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n;
    cin >> n; 
    vector<string> pat;
    vector<pair<string, int>> query(n);
    for (int i = 0; i < n; i++) {
        cin >> query[i].second >> query[i].first;
        pat.push_back(query[i].first);
    }
    AhoCorasick aho(pat);
    auto ret = aho.findAll(pat, s);
    vector<vector<int>> c(n); 
    for (int i = 0; i < sz(ret); i++) {
        for(auto &x : ret[i]) {
            c[x].push_back(i);
        }
    }
    for(int i = 0; i < n; i++) {
        sort(c[i].begin(), c[i].end());
        int k = query[i].second;
        int res = INT32_MAX;
        for (int j = k - 1; j < c[i].size(); j++) {
            res = min(res, int(c[i][j] - c[i][j - k + 1] + sz(query[i].first)));
        }
        cout << (res == INT32_MAX ? -1 : res) << '\n'; 
    }
    return 0;
}
