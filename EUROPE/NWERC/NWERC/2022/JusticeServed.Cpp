#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q,k;
int a[N + 1]; 
const double eps = 1e-9; 
int bit[N + 1];
int dp[N + 1]; 
struct query{
    int id,l,r;
} qry[N + 1]; 
int range(int i){
	     int c = 0;
	     for(++i; i > 0 ; i -= (i & -i)){
		     c = max(c, bit[i]);
       }
       return c;
}
void upd(int i,int dif) {
	  for(++i; i < N ; i += (i & -i)){
		   bit[i] = max(dif, bit[i]);
    }
}
bool cmp(query &a, query &b){
      return a.l == b.l ? a.r > b.r : a.l < b.l; 
}
signed main(){
      scanf("%d",&n);
      vector<int>val;
      for(int i = 1; i <= n; i++){
          scanf("%d%d",&qry[i].l,&qry[i].r); 
          qry[i].r  += qry[i].l;
          val.push_back(qry[i].l);
          val.push_back(qry[i].r); 
          qry[i].id = i; 
      }
      sort(val.rbegin(),val.rend());
      val.erase(unique(val.begin(),val.end()),val.end()); 
      sort(qry + 1, qry + n + 1,cmp);    
      for(int i = 1; i <= n; i++){
            int pos = lower_bound(val.begin(),val.end(),qry[i].r,greater<int>()) - val.begin(); 
            dp[qry[i].id] = 1 + range(pos);
            upd(pos,dp[qry[i].id]); 
      }
      for(int i = 1; i <= n; i++) printf("%d ",dp[i] - 1);
      return 0;
}