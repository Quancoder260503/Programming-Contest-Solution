#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1e6 + 200000;

struct Node {
  int len, link, cnt, firstpos;
  map<char, int> nxt;
};

Node node[maxf]; 
int N, sz, last;

void extend(char c) {
  int cur = sz++;
  node[cur].len = node[last].len + 1;
  int p = last;
  while (p != -1 && !node[p].nxt.count(c)) {
    node[p].nxt[c] = cur;
    p = node[p].link;
  }
  if (p == -1) {
    node[cur].link = 0;
  } else {
    int at = node[p].nxt[c];
    if (node[p].len + 1 == node[at].len) {
      node[cur].link = at;
    } else {
      int ncur = sz++;
      node[ncur].len = node[p].len + 1;
      node[ncur].nxt = node[at].nxt;
      node[ncur].link = node[at].link;
      while (p != -1 && node[p].nxt[c] == at) {
        node[p].nxt[c] = ncur;
        p = node[p].link;
      }
      node[at].link = node[cur].link = ncur;
    }
  }
  last = cur;
  return;
}

bool query(const string &q) {
  int m = sz(q), at = 0;
  for (int i = 0; i < m; i++) {
    if (!node[at].nxt.count(q[i])) return false;
    at = node[at].nxt[q[i]];
  }
  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S, Q;
  cin >> S >> Q; 
  for(int i = 0; i < 26; i++) { 
    S = S + '#' + char(i + 'A');
    S = S + '#' + char(i + 'a');  
  }
  S = S + '#' + '_'; 
  for(int i = 0; i < 10; i++) { 
    S = S + '#' + char(i + '0');
  }
  S = S + '#'; 
  node[0].link = -1;
  node[0].len = 0;
  sz = 1;
  last = 0;
  for (int i = 0; i < sz(S); i++) {
    extend(S[i]);
  }
  int ret = 0;
  for(;;) { 
    int lo = 0, hi = sz(Q); 
    while(lo < hi) { 
      int mid = (lo + hi + 1) / 2; 
      if(query(Q.substr(0, mid))) { 
        lo = mid; 
      }
      else { 
        hi = mid - 1; 
      }
    }
    ret++; 
    Q = Q.substr(lo);
    if(sz(Q) == 0) break;  
  }
  cout << ret << '\n'; 
  return 0;
}