#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 2e6 + 1;
const int mod = 1e9 + 7;
long long n,m,k,q;
long long pows[N + 1];
long long prime[N + 1]; 
long long dp[N + 1];
long long mo[N + 1];
bool vis[N + 1]; 
vector<int>primes[N];

template<class T> struct Trie {
	struct Node { 
        int cntl = 0;
        int cntr = 0;
		    int l = -1, r = -1; 
	};
	int B;
  int t;
	vector<Node> nodes;
	int newNode() { 
		  nodes.emplace_back();
		  return nodes.size() - 1;
	}
	void init(int _B) {
		  B = _B;
		  nodes.clear();
		  newNode();
	}
	void insert(int n) {
		int u = 0;
		for (int i = B; i >= 0; i--) {
			if ((n >> i) & 1) {
				if (nodes[u].r == -1) {
					nodes[u].r = newNode(); 
				}
        nodes[u].cntr++;
				u = nodes[u].r;
			} 
      else {
				if (nodes[u].l == -1) {
					nodes[u].l = newNode();
        }
         nodes[u].cntl++;
				 u = nodes[u].l;
			}
		} 
	}
	long long  query(int n) {
		int u = 0; 
    long long ans = 0;
		for (int i = B; i >= 0; i--) {
			if ((n >> i) & 1) {
				if (nodes[u].l != -1) {
					  u = nodes[u].l;
            ans += (1ll << i);
				} 
        else {
					u = nodes[u].r;
				}
			} 
      else {
				if (nodes[u].r != -1 ) {
					  u = nodes[u].r;
            ans += (1ll << i);
				} 
        else {
					u = nodes[u].l;
				}
			}
		}
		return ans;
	}
};
Trie<int>trie;
int main(){
    scanf("%d",&n); 
    trie.init(30);
    trie.insert(0);
    long long ans = 0;
    long long pref = 0; 
    for(int i = 1; i <= n; i++){
          long long x; scanf("%lld",&x);
          pref = (pref ^ x);
          ans = max(ans, trie.query(pref)); 
          trie.insert(pref);
    }
    printf("%lld\n",ans); 
}