#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,x,k,i,j,w,q;
string s;
struct node{
    ll r; ll l;
    ll x0l; ll x0r;
    ll x1l; ll x1r;
    ll x0val; ll x1val;
} tree[sz<<2];
void push(int p,int l,int mid ,int r){
    tree[p].x0val=max(tree[2*p].x0val,tree[2*p+1].x0val);
    tree[p].x1val=max(tree[2*p].x1val,tree[2*p+1].x1val);
    if(tree[2*p+1].x0val==(r-mid)) tree[p].x0r=tree[2*p+1].x0val+tree[2*p].x0r;
    if(tree[2*p+1].x1val==(r-mid)) tree[p].x1r=tree[2*p+1].x1val+tree[2*p].x1r;
    if(tree[2*p].x0val==(mid-l+1)) tree[p].x0l=tree[2*p].x0val+tree[2*p+1].x0l;
    if(tree[2*p].x1val==(mid-l+1)) tree[p].x1l=tree[2*p].x1val+tree[2*p+1].x1l;
    tree[p].x0r=max(tree[p].x0r,tree[2*p+1].x0r);
    tree[p].x0l=max(tree[p].x0l,tree[2*p].x0l);
    tree[p].x1r=max(tree[p].x1r,tree[2*p+1].x1r);
    tree[p].x1l=max(tree[p].x1l,tree[2*p].x1l);
    if(s[tree[2*p].r]=='0' and s[tree[2*p+1].l]=='0'){
        tree[p].x0val=max(tree[p].x0val,tree[2*p].x0r+tree[2*p+1].x0l);
    }
    else if(s[tree[2*p].r]=='1' and s[tree[2*p+1].l]=='1'){
        tree[p].x1val=max(tree[p].x1val,tree[2*p].x1r+tree[2*p+1].x1l);
    }
    tree[p].x0val=max(max(tree[p].x0r,tree[p].x0l),tree[p].x0val);
    tree[p].x1val=max(max(tree[p].x1r,tree[p].x1l),tree[p].x1val);
    tree[p].l=tree[2*p].l; tree[p].r=tree[2*p+1].r;
}
void reset(int p){
    tree[p].x0val=tree[p].x1val=tree[p].x0r=tree[p].x1r=tree[p].x0l=tree[p].x1l=0;
}
void build(int l=0,int r=n-1,int p=1){
    if(l==r){
        if(s[l]=='0') tree[p].x0val=tree[p].x0l=tree[p].x0r=1;
        else if(s[l]=='1') tree[p].x1val=tree[p].x1l=tree[p].x1r=1;
        tree[p].l=l; tree[p].r=r;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    push(p,l,mid,r);
}
void update(int L,int R ,int l=0,int r=n-1,int p=1){
    if(l>R or r<L) return;
    if(l==r){
        if(s[l]=='0'){
            s[l]='1';
            tree[p].x1val=tree[p].x1l=tree[p].x1r=1;
            tree[p].x0val=tree[p].x0l=tree[p].x0r=0;
        } else{
            s[l]='0';
            tree[p].x1val=tree[p].x1l=tree[p].x1r=0;
            tree[p].x0val=tree[p].x0l=tree[p].x0r=1;
        }
        return;
    } 
      int mid=(l+r)>>1;
      update(L,R,l,mid,2*p);
      update(L,R,mid+1,r,2*p+1);
      reset(p);
      push(p,l,mid,r);
}
int main(){
    cin>>s;
    n=s.length();
    build(); cin>>q;
    for(int i=0;i<q;i++){
        ll x;cin>>x; x--;
        update(x,x);
        ll res=max(tree[1].x0val,tree[1].x1val);
        cout<<res<<" ";
    } 
}