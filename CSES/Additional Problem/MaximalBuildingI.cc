#include <bits/stdc++.h>
#include <iostream>
#include<stack>
#include<queue>
#include<map>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz1=2e6+1;
const int sz=1001;
ll n,x,k,m,q,b,ans,re;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,3>>edge;
bool yes=0;
ll parent[sz];
ll compsize[sz];
ll ca[sz];
array<ll,2>a[sz];
ll fac[11];
ll dp[sz][sz];
ll d[sz][sz];
ll res=0;
ll oc[11];
char c[sz][sz];
const int mod=998244353;
int main(){
    cin>>n>>m;
    if(n<=0 and m<=0) {cout<<0;return 0;}
    stack<ll>stack;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(c[i][j]=='*') d[i][j]=0;
            if(i==0 and c[i][j]=='.') d[i][j]=1;
            if(i>0  and c[i][j]=='.') d[i][j]=d[i-1][j]+1;
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
               while (!stack.empty() and d[i][stack.top()]>=d[i][j]) stack.pop();
               ll wi=j-(stack.size() ? stack.top() : -1);
               dp[i][j]+=d[i][j]*wi;
               stack.push(j);
        }   
        while (!stack.empty()) stack.pop(); 
        for(int j=m-1;j>=0;j--){
              while (!stack.empty() and d[i][stack.top()]>=d[i][j]) stack.pop();
              ll wi=(stack.size() ? stack.top() : m) -j;
              dp[i][j]+=d[i][j]*(wi-1);
              res=max(res,dp[i][j]);
              stack.push(j);
        } 
        while (!stack.empty()) stack.pop(); 
    } cout<<res;
}