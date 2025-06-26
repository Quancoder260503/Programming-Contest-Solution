#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 1;
const int mod = 1e9 + 7;
long long n,m,k,q;
int newnode;
long long trie[N + 1][26];
bool vis[N + 1]; 
vector<int>primes[N];
long long dp[N + 1];
long long a[N + 1];
char p[N + 1];
char s[N + 1];
void add(const char *s){
     int itr = 0; 
     for(int i = 0; s[i];  i++){
          int pos = s[i] - 'a';
          if(!trie[itr][pos]) trie[itr][pos] = ++newnode;
          itr = trie[itr][pos]; 
     }
     a[itr] = 1;
}
int main(){
     scanf("%s%d",&s,&n); 
     for(int i = 1; i <= n; i++){
            scanf("%s",&p);
            add(p); 
     }
     int len = strlen(s);
     dp[len] = 1;
     for(int i = len - 1; i >= 0; i--){
          int u = 0;
          for(int j = i; j < len; j++){
                int t = s[j] - 'a'; 
                if(!trie[u][t]) break; 
                u = trie[u][t];
                if(a[u]) dp[i] += dp[j + 1]; 
          }
          dp[i] %= mod; 
     }
     printf("%lld\n",dp[0]);
}