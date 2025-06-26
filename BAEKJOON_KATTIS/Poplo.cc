#include "bits/stdc++.h"

using namespace std;

#define sz(x) x.size()

vector<pair<int, int>> ret;
vector<int>len; 

struct Trie
{
    vector<pair<char, Trie *>> ch;
    int end;
    Trie *fail;
    Trie()
    {
        end = -1;
        ch.clear();
        fail = nullptr;
    }
    void insert(const char *s, int num)
    {
        if (!*s)
        {
            end = num;
            return;
        }
        int now = *s - 'a';
        for (auto &i : ch)
        {
            if (i.first == now)
                return i.second->insert(s + 1, num);
        }
        ch.push_back({now, new Trie});
        ch.back().second->insert(s + 1, num);
    }
    void init()
    {
        queue<Trie *> q;
        q.push(this);
        while (!q.empty())
        {
            Trie *now = q.front();
            q.pop();
            for (auto &i : now->ch)
            {
                Trie *next = i.second;
                if (now == this)
                    next->fail = this;
                else
                {
                    Trie *t = now->fail;
                    while (t != this)
                    {
                        bool chk = true;
                        for (auto j : t->ch)
                        {
                            if (j.first == i.first)
                            {
                                chk = false;
                                break;
                            }
                        }
                        if (!chk)
                            break;
                        t = t->fail;
                    }
                    for (auto j : t->ch)
                    {
                        if (j.first == i.first)
                        {
                            t = j.second;
                            break;
                        }
                    }
                    next->fail = t;
                }
                if (next->fail->end >= 0)
                {
                    if (next->end == -1 || (len[next->fail->end] > len[next->end]))
                    {
                        next->end = next->fail->end;
                    }
                }
                q.push(next);
            }
        }
    }
    void query(const string &s)
    {
        Trie *cur = this;
        for (int i = 0; i < sz(s); i++)
        {
            int now = s[i] - 'a';
            while (cur != this)
            {
                bool chk = true;
                for (auto j : cur->ch)
                {
                    if (j.first == now)
                    {
                        chk = false;
                        break;
                    }
                }
                if (!chk)
                    break;
                cur = cur->fail;
            }
            for (auto j : cur->ch)
            {
                if (j.first == now)
                {
                    cur = j.second;
                    break;
                }
            }
            if (cur->end >= 0)
            {
                ret.push_back({i - len[cur->end] + 1, i + 1});
            }
        }
    }
};
int  main(void)
{
    int n, q;
    cin >> n;
    len.resize(n); 
    string Word;
    cin >> Word;
    cin >> q;
    Trie *root = new Trie; 
    for(int i = 0; i < q; i++)
    {
        string c; 
        cin >> c;
        len[i] = c.length(); 
        root -> insert(c.c_str(), i); 
    }
    root -> init(); 
    root -> query(Word);
    int ctr = 0;
    int last = 0;
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++)
    {
        if (last < ret[i].first)
        {
            ctr += ret[i].first - last;
        }
        last = max(last, ret[i].second);
    }
    ctr += n - last;
    cout << ctr << '\n';
    return 0;
}