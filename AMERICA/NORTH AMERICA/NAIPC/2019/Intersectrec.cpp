#include "bits/stdc++.h"
using namespace std;
#define N 200005 
int n; 
#define mp make_pair
vector<pair<int,int> >events[N];
vector<pair<int,int> >query[N]; 
struct Rec{ 
    long long xa,ya,xb,yb; 
} R[N];
int len;
struct fewwick{
   long long bit[N];
   long long sum(int i)
   {
	     long long c = 0;
	     for(++i; i > 0 ; i -= (i & -i))
         {
		     c = (c+bit[i]);
         }
         return c;
   }
   long long query(int l,int r)
   {
      return sum(r) - sum(l-1);
   }
   void upd(int i,int dif) 
   {
	   for(++i; i < N ; i += (i & -i))
       {
		   bit[i] = (dif+bit[i]);
       }
   }
} fenw;
signed main(void){
    scanf("%d",&n);
    vector<long long>corx;
    vector<long long>cory;  
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld%lld",&R[i].xa,&R[i].ya,&R[i].xb,&R[i].yb); 
        corx.push_back(R[i].xa); 
        cory.push_back(R[i].ya);
        corx.push_back(R[i].xb);
        cory.push_back(R[i].yb); 
    }
    sort(corx.begin(),corx.end());
    corx.erase(unique(corx.begin(),corx.end()),corx.end()); 
    sort(cory.begin(),cory.end());
    cory.erase(unique(cory.begin(),cory.end()),cory.end()); 
    for(int i = 1 ; i <= n; i++)
    {
        R[i].xa = lower_bound(corx.begin(),corx.end(),R[i].xa) - corx.begin() + 1; 
        R[i].ya = lower_bound(cory.begin(),cory.end(),R[i].ya) - cory.begin() + 1; 
        R[i].xb = lower_bound(corx.begin(),corx.end(),R[i].xb) - corx.begin() + 1; 
        R[i].yb = lower_bound(cory.begin(),cory.end(),R[i].yb) - cory.begin() + 1; 
    }
    for(int i = 1; i <= n; i++)
    {
        events[R[i].xa].push_back(mp(R[i].ya,1));
        events[R[i].xa].push_back(mp(R[i].yb,1)); 
        events[R[i].xb + 1].push_back(mp(R[i].ya,-1));
        events[R[i].xb + 1].push_back(mp(R[i].yb,-1)); 
        query[R[i].xa].push_back(mp(R[i].ya,R[i].yb)); 
        query[R[i].xb].push_back(mp(R[i].ya,R[i].yb)); 
    }
    long long ans = 0; 
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < events[i].size(); j++)
        {
            pair<int,int>curr = events[i][j];
            fenw.upd(curr.first,curr.second); 
        }
        for(int j = 0; j < query[i].size(); j++)
        {
            pair<int,int>curr = query[i][j];
            ans += fenw.query(curr.first ,curr.second); 
        }
    } 
    printf("%d\n",ans == 4 * n ? 0 : 1); 
    return 0; 
}