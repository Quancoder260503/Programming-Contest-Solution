#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 
const int MOD = 1e9 + 7; 

struct node { 
  int64_t len[2][2], cnt[2][2]; 
  node() { 
   for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) {
     cnt[i][j] = 0; 
     len[i][j] = oo; 
    }
   } 
   return; 
  } 
  node operator + (const node &other) { 
   node ret = node(); 
   for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) {
     for(int k = 0; k < 2; k++) { 
      if(ret.len[i][j] == oo) { 
       ret.len[i][j] = len[i][k] + other.len[k][j] - 1; 
       ret.cnt[i][j] = 1LL * cnt[i][k] % MOD * other.cnt[k][j] % MOD; 
      } else if(ret.len[i][j] > len[i][k] + other.len[k][j] - 1) { 
       ret.len[i][j] = len[i][k] + other.len[k][j] - 1; 
       ret.cnt[i][j] = 1LL * cnt[i][k] % MOD * other.cnt[k][j] % MOD; 
      }
      else if(ret.len[i][j] == len[i][k] + other.len[k][j] - 1) { 
        (ret.cnt[i][j] += 1LL * cnt[i][k] % MOD * other.cnt[k][j] % MOD) %= MOD; 
      }
     }
    }
   }
   return ret;  
  }
}; 

const int MAXN = 1e5 + 10; 
string S; 
int N, Q;
node tree[MAXN << 2], tree_mir[MAXN << 2]; 
int lazy[MAXN << 2];

void push_down(int p, int L, int mid, int R) { 
 if(lazy[p] != -1) { 
   if(lazy[p] < 2) { 
    for(int i = 0; i < 2; i++) { 
     for(int j = 0; j < 2; j++) {
      tree[2 * p].cnt[i][j] = tree[2 * p + 1].cnt[i][j] = tree_mir[2 * p].cnt[i][j] = tree_mir[2 * p + 1].cnt[i][j] = 0; 
      tree[2 * p].len[i][j] = tree[2 * p + 1].len[i][j] = tree_mir[2 * p].len[i][j] = tree_mir[2 * p + 1].len[i][j] = oo; 
     }
    } 
    int c = lazy[p]; 
    tree[2 * p].len[c][c ^ 1] = 2; 
    tree[2 * p].len[c][c] = mid - L + 2; 
    tree[2 * p].cnt[c][c ^ 1]     = tree[2 * p].cnt[c][c] = 1; 
    tree[2 * p].len[c ^ 1][c ^ 1] = tree[2 * p].cnt[c ^ 1][c ^ 1] = 1; 

    tree[2 * p + 1].len[c][c ^ 1] = 2; 
    tree[2 * p + 1].len[c][c] = R - mid + 1; 
    tree[2 * p + 1].cnt[c][c ^ 1]     = tree[2 * p + 1].cnt[c][c] = 1; 
    tree[2 * p + 1].len[c ^ 1][c ^ 1] = tree[2 * p + 1].cnt[c ^ 1][c ^ 1] = 1; 

    c = c ^ 1;

    tree_mir[2 * p].len[c][c ^ 1]     = 2; 
    tree_mir[2 * p].len[c][c] = mid - L + 2; 
    tree_mir[2 * p].cnt[c][c ^ 1]     = tree_mir[2 * p].cnt[c][c] = 1; 
    tree_mir[2 * p].len[c ^ 1][c ^ 1] = tree_mir[2 * p].cnt[c ^ 1][c ^ 1] = 1; 

    tree_mir[2 * p + 1].len[c][c ^ 1]     = 2; 
    tree_mir[2 * p + 1].len[c][c] = R - mid + 1; 
    tree_mir[2 * p + 1].cnt[c][c ^ 1]     = tree_mir[2 * p + 1].cnt[c][c] = 1; 
    tree_mir[2 * p + 1].len[c ^ 1][c ^ 1] = tree_mir[2 * p + 1].cnt[c ^ 1][c ^ 1] = 1; 

   } else { 
    swap(tree[2 * p], tree_mir[2 * p]);
    swap(tree[2 * p + 1], tree_mir[2 * p + 1]);  
   }
   if(lazy[2 * p] == -1) { 
    lazy[2 * p] = lazy[p]; 
   } else { 
    if(lazy[p] < 2) lazy[2 * p] = lazy[p]; 
    else if(lazy[2 * p] == 2) lazy[2 * p] = -1; 
    else lazy[2 * p] = lazy[2 * p] ^ 1; 
   }
   if(lazy[2 * p + 1] == -1) { 
    lazy[2 * p + 1] = lazy[p]; 
   } else { 
    if(lazy[p] < 2) lazy[2 * p + 1] = lazy[p]; 
    else if(lazy[2 * p + 1] == 2) lazy[2 * p + 1] = -1; 
    else lazy[2 * p + 1] = lazy[2 * p + 1] ^ 1; 
   }
   //lazy[2 * p] = lazy[2 * p + 1] = lazy[p]; 
   lazy[p] = -1; 
 }
 return;  
}

void update(int c, int L, int R, int tl = 1, int tr = N, int p = 1) { 
 if(L > tr || R < tl) return; 
 if(L <= tl && tr <= R) {
  if(c < 2) { 
    for(int i = 0; i < 2; i++) { 
     for(int j = 0; j < 2; j++) {
      tree[p].cnt[i][j] = tree_mir[p].cnt[i][j] = 0; 
      tree[p].len[i][j] = tree_mir[p].len[i][j] = oo; 
     }
    } 
    tree[p].len[c][c] = tr - tl + 2; 
    tree[p].len[c][c ^ 1] = 2; 
    tree[p].cnt[c][c ^ 1] = tree[p].cnt[c][c] = 1; 
    tree[p].len[c ^ 1][c ^ 1] = tree[p].cnt[c ^ 1][c ^ 1] = 1; 
    c = c ^ 1; 
    tree_mir[p].len[c][c] = tr - tl + 2; 
    tree_mir[p].len[c][c ^ 1]     = 2; 
    tree_mir[p].cnt[c][c ^ 1]     = tree_mir[p].cnt[c][c] = 1; 
    tree_mir[p].len[c ^ 1][c ^ 1] = tree_mir[p].cnt[c ^ 1][c ^ 1] = 1; 
    c = c ^ 1; 
  } else { 
    swap(tree[p], tree_mir[p]); 
  }
  if(lazy[p] == -1) { 
    lazy[p] = c; 
   } else { 
    if(c < 2) lazy[p] = c; 
    else if(lazy[p] == 2) lazy[p] = -1; 
    else lazy[p] = lazy[p] ^ 1; 
  }
  return; 
 }
 int mid = (tl + tr) / 2;
 push_down(p, tl, mid, tr);  
 update(c, L, R, tl, mid, p << 1); 
 update(c, L, R, mid + 1, tr, p << 1 | 1); 
 tree[p]     = tree[p << 1] + tree[p << 1 | 1]; 
 tree_mir[p] = tree_mir[p << 1]  + tree_mir[p << 1 | 1]; 
 return; 
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  memset(lazy, -1, sizeof(lazy)); 
  cin >> N >> Q >> S;
  S = " " + S;
  for(int i = 1; i <= N; i++) { 
    update(S[i] - '0', i, i); 
  }
  for(int iter = 0, L, R; iter < Q; iter++) {
   char c; 
   cin >> c >> L >> R; 
   if(c == 'F') { 
    update(2, L, R); 
   } else { 
    update(c - '0', L, R); 
   } 
   int ret = oo; 
   int64_t cc = 0; 
   for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) { 
  //    cout << i << " " << j << " " << tree[1].len[i][j] << " " << tree[1].cnt[i][j] << '\n'; 
      if(ret > tree[1].len[i][j]) { 
        ret = tree[1].len[i][j]; 
        cc  = tree[1].cnt[i][j]; 
      } else if(ret == tree[1].len[i][j]) { 
        cc += tree[1].cnt[i][j]; 
        cc %= MOD; 
      }
    }
   }
   cout << ret << " " << cc << '\n'; 
 //  cout << "-----------------------\n"; 
  }
  return 0; 
}