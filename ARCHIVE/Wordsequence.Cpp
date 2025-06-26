#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 1;
const int mod = 1e9 + 7;
long long n,m,k,q;
int newnode;
long long trie[N + 1][26];
bool vis[N + 1]; 
vector<int>primes[N];
int dp[N + 1];
int a[N + 1];
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
     scanf("%d",&n); 
     for(int i = 1; i <= n; i++){
            scanf("%s",&s);
            add(s); 
     }
     for(int i = newnode; i >= 0; i--){
            for(int j = 0; j < 26; j++){
                 dp[i] = max(dp[i],dp[trie[i][j]]); 
            }
            dp[i] += a[i]; 
     }
     printf("%d\n",dp[0]);
}