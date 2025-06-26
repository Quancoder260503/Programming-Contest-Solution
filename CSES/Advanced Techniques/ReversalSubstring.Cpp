#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pii>adj[N + 1];
bool vis[N + 1];
char s[N + 1];
struct Node{
     char val;
     bool rev; 
     int weight,size; 
     Node *left, *right; 
     Node(char c): val(c), rev(0), weight(rand()), size(1), left(NULL), right(NULL) {} 
} *root;
int sizeo(Node *treap){
      return treap ? treap -> size : 0; 
}
void reverse(Node *x){
      if(!x) return;
      x -> rev = x -> rev xor 1; 
}
void add(Node *x){
      if(!x) return; 
      x -> size = 1 + sizeo(x -> left) + sizeo(x -> right); 
}
void push(Node *x){
      if(!x) return;
      if(x -> rev){
           swap(x -> left, x -> right);
           reverse(x -> left);
           reverse(x -> right); 
           x -> rev = 0; 
      }
}
Node *merging(Node *x, Node *y){
       if(!x | !y) return x ? x : y; 
       push(x); push(y);
       if(x -> weight < y -> weight){
             x -> right = merging(x -> right,y); 
             add(x);
             return x;
       }
       else{
            y -> left = merging(x,y -> left);
            add(y); 
            return y; 
       }
}
pair<Node *, Node *> split(Node *x,int k){
       if(!x) return {NULL,NULL};
       pair<Node *,Node *> y = {NULL,NULL};
       push(x); 
       if(k <= sizeo(x -> left)){
             y =  split(x -> left,k);
             x -> left = y.second;
             add(x); 
             y.second = x; 
       }
       else{
             y = split(x -> right, k - sizeo(x -> left) - 1); 
             x -> right = y.first;
             add(x);
             y.first = x; 
       }
       return y;
}
void heap(Node *x){
      if(!x) return;
      Node *maxi = x; 
      if(x -> left && x -> left -> weight > maxi -> weight) maxi = x -> left;
      if(x -> right && x -> right -> weight > maxi -> weight) maxi = x -> right; 
      if(maxi != x){
            swap(x -> weight,maxi -> weight);
            heap(maxi); 
      }
}
Node *build(int pos,int sz){ 
       if(sz == 0) return NULL;
       int mid = sz / 2;
       Node *x = new Node(s[pos + mid]); 
       x -> left = build(pos,mid);
       x -> right = build(pos + mid + 1, sz - mid - 1); 
       heap(x);
       add(x); 
       return x;
}
void reverse(int l,int sz){
      pair<Node *, Node *>x,y;
      x = split(root,l - 1);
      y = split(x.second,sz);
      reverse(y.first);
      x.second = merging(y.first,y.second);
      root = merging(x.first,x.second); 
}
void print(Node *x){
      if(!x) return;
      push(x);
      print(x -> left);
      printf("%c",x -> val);
      print(x -> right); 
}
int main(){
     scanf("%d%d",&n,&q);
     scanf("%s",s);
     root = build(0,n);
     for(int i = 0; i < q; i++){
           int l,r; 
           scanf("%d%d",&l,&r);
           reverse(l,r - l + 1); 
     }
     print(root); 
     return 0;     
}