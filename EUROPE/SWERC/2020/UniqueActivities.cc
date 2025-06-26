#include "bits/stdc++.h"

using namespace std;

const int N = 6e5 + 9;

struct SuffixAutomaton {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last, max_depth;
    vector<node> t;
    vector<int> terminal;
    vector<long long> dp;
    vector<vector<int>> depth; 
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n) {
        t.resize(2 * n);
        terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1);
        sz = 1;
        last = 0;
        g.resize(2 * n);
        depth.resize(2 * n); 
        t[0].len = 0;
        t[0].link = -1;
        t[0].firstpos = 0;
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1)
            t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree() {
        for (int i = 1; i < sz; i++)
            g[t[i].link].push_back(i);
    }
    void build(string &s) {
        for (auto x : s) {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    void dfs(int u, int p, int sum) {
        int is_leaf = true; 
        for (auto &x : g[u]) {
            dfs(x, u, sum + t[u].len - t[p].len);
            is_leaf = false;
        }
        if(is_leaf) {
            depth[sum + 1].push_back(t[u].firstpos - 1);
        }
        return; 
    }
    pair<int, int> solve(void) { 
        dfs(0, 0, 0);
        for (int i = 0; i < int(depth.size()); i++) if(depth[i].size() > 0) {
            sort(depth[i].rbegin(), depth[i].rend());
            return {i, depth[i].back()};
        }
        return {-1, -1};
    }
};

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    SuffixAutomaton st(s.size());
    st.build(s);
    auto res = st.solve();
    auto ret = s.substr(res.second - res.first + 1, res.first);
    cout << ret << '\n';
    return 0;
}