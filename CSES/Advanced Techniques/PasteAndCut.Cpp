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
struct Node{
     char val;
     int weight,size; 
     Node *left, *right; 
     Node(char c): val(c), weight(rand()), size(1), left(NULL), right(NULL) {} 
} *root;
int sizeo(Node *treap){
      return treap ? treap -> size : 0; 
}
void merge(Node *&treap, Node *left, Node *right){
       if(left == NULL){
            treap = right;
            return; 
       }
       if(right == NULL){
            treap = left;
            return; 
       }
       if(left -> weight < right -> weight){
             merge(left -> right, left -> right,right);   
             treap = left; 
       }
       else{
             merge(right -> left,left, right -> left);
             treap = right; 
       }
       treap -> size = 1 + sizeo(treap -> left) + sizeo(treap -> right); 
}
void split(Node *treap, Node *&left, Node *&right,int val){
      if(!treap){
            left = right = NULL;
            return; 
      }
      if(sizeo(treap -> left) < val){ 
           split(treap -> right, treap -> right,right,val - 1 - sizeo(treap -> left));
           left = treap; 
      }
      else{
           split(treap -> left, left,treap -> left,val);
           right = treap; 
      }
      treap -> size = 1 + sizeo(treap -> left) + sizeo(treap -> right); 
} 
ostream &operator<<(ostream &os, Node *n){
     if(!n) return os; 
     os << n -> left;
     os << n -> val;
     os << n -> right; 
     return os; 
}
int main(){
     scanf("%d%d",&n,&q);
     char s[N + 1];
     scanf("%s",&s);
     for(int i = 0; s[i]; i++){
           merge(root,root,new Node(s[i])); 
     }
     for(int i = 1; i <= q; i++){
           int l,r; scanf("%d%d",&l,&r);
           Node *a, *b, *c, *d;
           split(root,a,b,l - 1);
           split(b,c,d, r - l + 1);
           merge(root, a, d); 
           merge(root, root, c); 
     }
     cout << root << endl;
     return 0; 
}