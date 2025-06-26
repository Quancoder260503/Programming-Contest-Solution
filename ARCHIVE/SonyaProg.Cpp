#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef pair<int,int> pii;
typedef vector<pii> vpi;
typedef vector<int> vi; 
typedef pair<int,int> pi; 
#define f first  
#define s second
typedef long long ll;
const int N = 5e5 + 10;
const int M = 110;
const long long INF = 1e17; 
long long n,k,m;
long long dp[N + 1];
long long a[N + 1];
long long p[N + 1];
template<class T, int SZ> struct OffBIT2D { 
  // Code copied from BenQ template.
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() { 
    assert(!mode); mode = 1;
	  int lst[SZ]; 
    for(int i = 0; i < SZ; i++){
         lst[i] = cnt[i] = 0;
    }
    sort(todo.begin(),todo.end(),[](const pi& a, const pi& b) { 
			return a.s < b.s; });
		for(auto &t: todo){ 
         for (int x = t.f; x < SZ; x += x&-x){
			        if (lst[x] != t.s){
                  lst[x] = t.s, cnt[x] ++;
                }
         }
    }
		int sum = 0; 
    for(int i = 0; i < SZ; i++){
         lst[i] = 0, st[i] = (sum += cnt[i]);
    }
    val.resize(sum); bit.resize(sum); reverse(todo.begin(),todo.end());
		for(auto &t: todo){
         for (int x = t.f; x < SZ; x += x&-x){
			       if (lst[x] != t.s){
                  lst[x] = t.s, val[--st[x]] = t.s;
              }
          }
      }
	}
	int rank(int y, int l, int r) {
		return upper_bound(begin(val)+l,begin(val)+r,y)-begin(val)-l; 
  }
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y){
			bit[st[x]+y-1] += t; 
    }
  }
	void upd(int x, int y, T t) { 
		 if (!mode) todo.push_back({x,y});
		 else for (;x<SZ;x+=x&-x) UPD(x,y,t); 
  }
	int QUERY(int x, int y) { 
    T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
		return res; 
  }
	T query(int x, int y) { 
    assert(mode);
		T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
		return res; 
  }
	T query(int xl, int xr, int yl, int yr) {
    return query(xr,yr)-query(xl-1,yr) - query(xr,yl-1)+query(xl-1,yl-1); 
  }
};
int main(){
      scanf("%d",&n);
      OffBIT2D <int,N> fenw;
      for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
      for(int i = 1; i <= n; i++) scanf("%d",&p[i]);
      long long ans = 0;
      for(int i = 1; i <= n; i++){
           fenw.upd(p[i],a[p[i]],0); 
      }
      fenw.init();
      for(int i = 1; i <= n; i++){
            ans +=  fenw.query(p[i] - 1,n) - fenw.query(p[i] - 1,a[p[i]]);
            ans +=  fenw.query(n, a[p[i]] - 1) - fenw.query(p[i],a[p[i]] - 1); 
            printf("%lld\n",ans); 
            fenw.upd(p[i],a[p[i]],1); 
      }
      return 0; 
}