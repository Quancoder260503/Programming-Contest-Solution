#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long int64;
const int sz = 1e7 + 1;
int n,q,p;
long long a[sz];
int bit[sz];
long long res[sz];
template<class T> struct Seg {
    const T ID=1e18;
    T comb(T a,T b){return min(a,b);}
    int n; vector<T>seg;
    void init(int p){n=p;seg.assign(2*n,ID);}
    void pull(int p){seg[p]=comb(seg[2*p],seg[2*p+1]);}
    void upd(int p ,T val){
        seg[p]=min(seg[p+=n],val);
        for (p/=2;p;p/=2) pull(p);
    }
    T query(int l,int r){
        T ra=ID;T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if (l&1) ra=comb(ra,seg[l++]);
            if (r&1) rb=comb(rb,seg[--r]);
        }return comb(ra,rb);
    }
};
Seg<int64>st;
int main(){
      cin>>n>>p;
      vector<int64>ycor;
      vector<array<int64,4>>points;
      for(int i=1;i<=p;i++){
           int64 x1,y1,x2,y2;
           cin>>x1>>y1>>x2>>y2;
           points.push_back({x1,y1,i,-1});
           points.push_back({x2,y2,i,1});
           ycor.push_back(y1);
           ycor.push_back(y2);
      }
      st.init(2*p);
      st.upd(0,0);
      sort(ycor.begin(),ycor.end());
      sort(points.begin(),points.end());
      for(int i = 0; i < points.size(); i++){
            if(points[i][3]==-1){
                 int pos = lower_bound(ycor.begin(),ycor.end(),points[i][1])-ycor.begin();
                 res[points[i][2]] = st.query(0,pos) + points[i][0] + points[i][1];
            }
            else{
                 int pos = lower_bound(ycor.begin(),ycor.end(),points[i][1])-ycor.begin();
                 st.upd(pos,(1ll)*(res[points[i][2]]-points[i][0]-points[i][1]));
            }
      }
      cout<<(1ll)*(2*n + st.query(0,2*p-1))<<endl;
}