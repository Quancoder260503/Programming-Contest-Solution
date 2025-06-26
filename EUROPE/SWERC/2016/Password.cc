#include "bits/stdc++.h"

using namespace std;

#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], done = false, start = -1, end = -1, nmatches = 0;
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
    N[n].nmatches++;
    N[n].done = true; 
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
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  vector<int> find(string word) {
    int n = 0;
    vector<int> res;  // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<vector<int>> findAll(vector<string> &pat, string word) {
    vector<int> r = find(word);
    vector<vector<int>> res(sz(word));
    for (int i = 0; i < sz(word); i++) {
      int ind = r[i];
      while (ind != -1) {
        res[i - sz(pat[ind]) + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};

const int mod = 1000003;

const int maxc = 25; 
const int maxf = 20000; 

int64_t dyn[maxc][2][2][2][maxf];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int a, b, n; 
  cin >> a >> b >> n;
  vector<string>pat(n), pattern; 
  for(int i = 0; i < n; i++) { 
    cin >> pat[i]; 
  }
  for(int i = 0; i < n; i++) { 
    int flag = true; 
    for(int j = 0; j < n; j++) if(i != j) { 
      flag &= !(strstr(pat[i].c_str(), pat[j].c_str())); 
    }
    if(flag) pattern.push_back(pat[i]); 
  }
  unordered_map<int, char>mp;
  mp[0] = 'o', mp[1] = 'i', mp[3] = 'e', mp[5] = 's', mp[7] = 't'; 
  AhoCorasick aho(pattern); 
  memset(dyn, -1, sizeof(dyn)); 
  function<int64_t(int, int, int, int, int)> memo = [&](int len, int hasDigit, int hasCap, int hasLower, int nodeId) -> int64_t { 
    if(len == 0) return (hasDigit & hasLower & hasCap); 
    int64_t &ret = dyn[len][hasDigit][hasCap][hasLower][nodeId]; 
    if(ret != -1) return ret;
    ret = 0; 
    for(int c = 0; c < 26; c++) { 
      int nextNode = aho.N[nodeId].next[c]; 
      if(aho.N[nextNode].done) continue; 
      ret += memo(len - 1, hasDigit, true, hasLower, nextNode); 
      ret %= mod; 
      ret += memo(len - 1, hasDigit, hasCap, true, nextNode); 
      ret %= mod; 
    }
    for(int digit = 0; digit < 10; digit++) { 
      if(mp.count(digit)) { 
        int nextNode = aho.N[nodeId].next[mp[digit] - aho.first]; 
        if(aho.N[nextNode].done) continue; 
        ret += memo(len - 1, true, hasCap, hasLower, nextNode); 
        ret %= mod; 
      }
      else { 
        ret += memo(len - 1, true, hasCap, hasLower, 0); 
        ret %= mod; 
      }
    }
    return ret; 
  }; 
  int64_t ret = 0; 
  for(int i = a; i <= b; i++) { 
    ret += memo(i, false, false, false, 0); 
    ret %= mod; 
  }
  cout << ret << '\n'; 
  return 0;
}
/*

*/