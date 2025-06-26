#include <bits/stdc++.h>
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int maxf = 1e5 + 10;
const int64_t oo = 1e17; 
 
struct node {
  int64_t val, sum, lsum, rsum;
  node(int64_t _val = 0, int64_t _sum = 0, int64_t _lsum = 0, int64_t _rsum = 0)
      : val(_val), sum(_sum), lsum(_lsum), rsum(_rsum){};
  node operator+(node b) {
    node ret = node();
    ret.val = max({val, b.val, rsum + b.lsum});
    ret.rsum = max(b.rsum, b.sum + rsum);
    ret.lsum = max(lsum, sum + b.lsum);
    ret.sum = b.sum + sum;
    return ret;
  }
};
 
node tree[maxf << 2], nullNode;
int N, M, Q; 
 
void update(int64_t val, int pos, int l = 1, int r = N, int p = 1) { 
 if(l == r) { 
  tree[p].val = tree[p].sum = tree[p].lsum = tree[p].rsum = val; 
  return; 
 } 
 int mid = (l + r) / 2; 
 if(pos <= mid) update(val, pos, l, mid, 2 * p); 
 else update(val, pos, mid + 1, r, 2 * p + 1); 
 tree[p] = tree[2 * p] + tree[2 * p + 1]; 
 return; 
} 
 
node query(int L, int R, int l = 1, int r = N, int p = 1) { 
 if(L > r || R < l) return nullNode; 
 if(L <= l && r <= R) return tree[p]; 
 int mid = (l + r) / 2; 
 //cerr << l << " " << r << " " << L << " " << R << '\n'; 
 return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1); 
} 
 
vector<array<int, 3>>q[maxf]; 
 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> M >> N; 
  for(int i = 0, l, r, x; i < N; i++) { 
   cin >> l >> r >> x; 
   q[l].push_back({-1, x, i + 1});
   q[r + 1].push_back({-2, 0, i + 1}); 
  } 
  cin >> Q; 
  vector<int64_t>ret(Q); 
  for(int i = 0, k, s, t; i < Q; i++) { 
   cin >> k >> s >> t; 
   q[k].push_back({i, s, t}); 
  }
  nullNode.val = nullNode.rsum = nullNode.lsum = -oo; 
  for(int i = 0; i <= M; i++) { 
   for(int j = 0; j < sz(q[i]); j++) { 
    if(q[i][j][0] == -1) { 
      update(q[i][j][1], q[i][j][2]);
    } 
    else if(q[i][j][0] == -2) { 
      update(0, q[i][j][2]);
    }
    else { 
      auto [ind, s, t] = q[i][j]; 
      ret[ind] = query(s, t).val; 
    } 
   } 
  } 
  for(int i = 0; i < Q; i++) { 
   cout << ret[i] << '\n'; 
  } 
  return 0;
}