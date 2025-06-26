#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int maxf = 2e5 + 10;
const int64_t oo = 1e17; 
 
struct node {
  int64_t largest, second_largest, cnt_largest, cnt_second_largest;
  node(int64_t _largest = 0, int64_t _second_largest = 0, int64_t _cnt_largest = 0, int64_t _cnt_second_largest = 0)
      : largest(_largest), 
        second_largest(_second_largest), 
        cnt_largest(_cnt_largest), 
        cnt_second_largest(_cnt_second_largest){};
  node operator + (node b) {
    node ret = node();
    if(largest > b.largest) { 
     ret.largest = largest; 
     ret.cnt_largest = cnt_largest; 
     if(second_largest < b.largest) { 
       ret.second_largest = b.largest; 
       ret.cnt_second_largest = b.cnt_largest; 
     } else if(second_largest > b.largest) { 
       ret.second_largest = second_largest; 
       ret.cnt_second_largest = cnt_second_largest; 
     } else if(second_largest == b.largest) { 
       ret.second_largest = second_largest; 
       ret.cnt_second_largest = cnt_second_largest + b.cnt_largest; 
     }
    } else if(largest < b.largest) { 
     ret.largest = b.largest; 
     ret.cnt_largest = b.cnt_largest; 
     if(largest < b.second_largest) { 
       ret.second_largest = b.second_largest; 
       ret.cnt_second_largest = b.cnt_second_largest; 
     } else if(largest > b.second_largest) { 
       ret.second_largest = largest; 
       ret.cnt_second_largest = cnt_largest; 
     } else if(largest == b.second_largest) { 
       ret.second_largest = largest; 
       ret.cnt_second_largest = cnt_largest + b.cnt_second_largest; 
     }
    } else { 
     ret.largest = largest; 
     ret.cnt_largest = cnt_largest + b.cnt_largest; 
      if(second_largest < b.second_largest) { 
       ret.second_largest = b.second_largest; 
       ret.cnt_second_largest = b.cnt_second_largest; 
     } else if(second_largest > b.second_largest) { 
       ret.second_largest = second_largest; 
       ret.cnt_second_largest = cnt_second_largest; 
     } else if(second_largest == b.second_largest) { 
       ret.second_largest = second_largest; 
       ret.cnt_second_largest = cnt_second_largest + b.cnt_second_largest; 
     }
    }
    return ret;
  }
};
 
node tree[maxf << 2], nullNode;
int N, M, Q; 
 
void update(int64_t val, int pos, int l = 1, int r = N, int p = 1) { 
 if(l == r) { 
  tree[p].largest = val, tree[p].cnt_largest = 1, tree[p].cnt_second_largest = 0, tree[p].second_largest = 0; 
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


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 cin >> N >> Q; 
 for(int i = 1, x; i <= N; i++) { 
  cin >> x; 
  update(x, i); 
 }
 for(int i = 0, c, l, r, p, x; i < Q; i++) { 
  cin >> c; 
  if(c == 1) {
    cin >> p >> x; 
    update(x, p); 
  } else { 
    cin >> l >> r; 
    auto cc = query(l, r); 
    cout << cc.cnt_second_largest << '\n'; 
  }
 }
 return 0; 
}