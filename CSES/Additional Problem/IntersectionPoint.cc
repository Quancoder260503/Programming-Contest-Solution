#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int sz = 1e7 + 1;
int n,q;
long long a[sz];
vector<array<int,4>>pos;
int bit[sz];
int sum(int i)
{
	  int c=0;
	  for(++i; i > 0 ; i -= (i & -i))
		   c+= bit[i];
	  return c;
}
void upd(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		 bit[i] += dif;
}
int main(){
       cin>>n;
       for(int i = 1; i <= n; i++){
            int xa,xb,ya,yb;
            cin>>xa>>ya>>xb>>yb;
            if(ya==yb) pos.push_back({ya,1,xa,xb});
            else{
                pos.push_back({ya,2,xa,1});
                pos.push_back({yb,3,xb,1});
            }
       }
       sort(pos.begin(),pos.end());
       long long ans = 0; 
       for(int i = 0; i < pos.size(); i++){
             pos[i][2]+=1000001; pos[i][3]+=1000001;
             if(pos[i][1]==1) ans+=sum(pos[i][3])-sum(pos[i][2]-1);
             else if(pos[i][1]==2) upd(pos[i][2],1);
             else if(pos[i][1]==3) upd(pos[i][2],-1);
       }
       cout<<ans<<endl;
}
