#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=501;
const int sz1=1e5+1;
int n,x,k,i,j,w;
ll res=1e18;
ll ans=0;
string s;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
char c[sz1];
ll a[sz];
vector<ll>adj[sz];
ll dp[sz][sz];
ll d[sz1];
ll d1[sz][sz];
const int mod=1e9+7;
ll nCr(int x,int y){
    if (x>y or x<0 or y<0) return 0;
    if (x==0) return 1;
    if(x<=1 and y<=1) return 1;
    if (d1[x][y]>0) return d1[x][y];
    d1[x][y]=nCr(x-1,y-1)%mod+nCr(x,y-1)%mod;
    return nCr(x-1,y-1)+nCr(x,y-1);
}
int main(){
    cin>>s;
    n=s.length();
    for (int i=n-1;i>=0;i--){
        for (int j=i+1;j<n;j=j+2){
            if (j==i+1 and s[i]==s[j]) dp[i][j]++;
            for(int k=i+1;k<=j;k=k+2){
                ll p=nCr((k-i+1)/2,(j-i+1)/2)%mod;
                if(s[i]==s[k] and k>i+2) dp[i][j]+=dp[i+1][k-1]%mod*dp[k+1][j]%mod*p%mod;
                if (s[i]==s[k] and k==i+1) dp[i][j]+=dp[i][k]%mod*dp[k+1][j]%mod*p%mod;
                if (s[i]==s[k] and k==j) dp[i][j]+=dp[i+1][k-1]%mod*p%mod;
                dp[i][j]%=mod;
            }
        }
    } cout <<dp[0][n-1]%mod;
}