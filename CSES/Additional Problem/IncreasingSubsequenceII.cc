#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int n,q;
int trs[sz];
vector<int>adj[sz];
vector<int>ord;
bool vis[sz];
int cnt[sz];
int d[sz]; 
ll bit[sz];
map<int,int>mp;
ll query(int i)
{
	int c=0;
	for(++i; i > 0 ; i -= (i & -i))
		c= (c+bit[i])%mod;
	return c;
}
void upd(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] = (dif+bit[i])%mod;
}
int main(){
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    int timer=1;
    for(auto &it:mp){
        it.second=timer++;
    }
    ll ans=0;
    for(int &x:a){
        x=mp[x];
    }
    for(auto x:a){
        ll k=query(x-1)+1;
        ans=(ans+k)%mod;
        upd(x,k);
    }
    cout<<ans<<endl;
}