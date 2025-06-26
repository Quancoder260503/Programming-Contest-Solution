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
const int sz=2e5+1;
ll n,x,k,m,q,b,c,ans,re;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,3>>edge;
bool yes=0;
ll parent[sz];
ll compsize[sz];
ll dp[sz];
ll ca[sz];
array<ll,2>a[sz];
ll fac[11];
ll d[sz];
ll res=0;
ll oc[11];
const int mod=998244353;
int main(){
    cin>>n;
    if(n<=0) {cout<<0;return 0;}
    stack<ll>stack;
    for(int i=0;i<n;i++)cin>>d[i];
    for(int i=0;i<n;i++){
        while (!stack.empty() and d[stack.top()]>=d[i]) stack.pop();
        ll wi=i-(stack.size() ? stack.top() : -1);
        dp[i]+=d[i]*wi;
        stack.push(i);
    } 
    while (!stack.empty()) stack.pop();
    for(int i=n-1;i>=0;i--){
        while (!stack.empty() and d[stack.top()]>=d[i]) stack.pop();
        ll wi=(stack.size() ? stack.top() : n) -i;
        dp[i]+=d[i]*(wi-1);
        res=max(res,dp[i]);
        stack.push(i);
    } cout<<res;
}