#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], start = -1, end = -1;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    return; 
  }
  AhoCorasick(vector<string> &pat) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      insert(pat[i], i);
    }
    N[0].back = sz(N);
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < alpha; i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1)
          ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          q.push(ed);
        }
      }
    }

  }
  vector<int> find(string word) {
   int n = 0;
   vector<int> res; // ll count = 0;
   for (char c : word) {
    n = N[n].next[c - first];
	res.push_back(N[n].end);
   }
   return res;
  }
  vector<vector<int>> findAll(vector<string>& pat, string word) {
   vector<int> r = find(word);
   vector<vector<int>> res(sz(pat));
   for(int i = 0; i < sz(word); i++) {
	int ind = r[i];
	while (ind != -1) {
	 res[ind].push_back(i - sz(pat[ind]) + 1);
	 ind = backp[ind];
	}
   }
   return res;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string word; 
  cin >> word; 
  int q; 
  cin >> q; 
  vector<pair<string, int>>query(q); 
  vector<string>pattern; 
  for(int i = 0; i < q; i++) { 
   cin >> query[i].first >> query[i].second; 
   pattern.push_back(query[i].first); 
  }
  sort(pattern.begin(), pattern.end()); 
  pattern.erase(unique(pattern.begin(), pattern.end()), pattern.end()); 
  AhoCorasick aho(pattern); 
  vector<vector<int>> indApps = aho.findAll(pattern, word); 
  for(int i = 0; i < q; i++) { 
   int pos = lower_bound(pattern.begin(), pattern.end(), query[i].first) - pattern.begin(); 
   cout << (query[i].second > sz(indApps[pos]) ? -1 : 
            indApps[pos][query[i].second - 1] + 1) << '\n'; 
  }
  return 0; 
}
