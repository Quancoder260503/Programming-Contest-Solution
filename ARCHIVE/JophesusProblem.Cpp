#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q;
int a[N + 1]; 
const double eps = 1e-9;
template <class T> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
signed main(){
      scanf("%d",&n);
      Tree<int>trs;
      for(int i = 1; i <= n; i++){
           trs.insert(i); 
      }
      int pos = 1;
      while(trs.size()){
           pos = pos % trs.size();
           int ans = *trs.find_by_order(pos);
           cout << ans << ' '; 
           trs.erase(ans); 
           pos++;
      }
      return 0;
}