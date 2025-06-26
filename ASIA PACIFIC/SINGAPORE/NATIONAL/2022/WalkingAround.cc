#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 10; 
const int LOG = 31; 

int dist[maxf]; 
vector<pair<int, int>>g[maxf]; 
int n; 

struct Node {
    Node *c[2];
};

void insert(Node *node, int x, int bit){
    if (bit < 0) return; 
    if (x & (1 << bit)) {
        if (!node->c[1]) node->c[1] = new Node();
        insert(node->c[1], x, bit - 1);
    }
    else {
        if (!node->c[0]) node->c[0] = new Node();
        insert(node->c[0], x, bit - 1);
    }
    return; 
}
int64_t query_min(Node *node, int x, int bit) {
    if (bit < 0) return 0; 
    if (x & (1 << bit)) {
        if(node->c[1]) return query_min(node->c[1], x, bit - 1);
        else if(node->c[0]) return (1LL << bit) + query_min(node->c[0], x, bit - 1);  
    }
    else {
        if (node->c[0]) return query_min(node->c[0], x, bit - 1);
        else if(node->c[1]) return (1LL << bit) + query_min(node->c[1], x, bit - 1);
    }
    return 0; 
}

int64_t query_max(Node *node, int x, int bit)
{
    if (bit < 0) return 0;
    if (x & (1 << bit)) {
        if (node->c[0]) return (1LL << bit) + query_max(node->c[0], x, bit - 1);
        else if(node->c[1]) return query_max(node->c[1], x, bit - 1);
    }
    else {
        if (node->c[1]) return (1LL << bit) + query_max(node->c[1], x, bit - 1);
        else if(node->c[0]) return query_max(node->c[0], x, bit - 1);
    }
    return 0;
}

void dfs(int u, int p) { 
    for(auto [v, w] : g[u]) { 
        if(v == p) continue; 
        dist[v] = dist[u] ^ w; 
        dfs(v, u); 
    }
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cin >> n; 
    for(int i = 0, u, v, w; i < n - 1; i++) { 
        cin >> u >> v >> w;
        g[--u].push_back({--v, w});
        g[v].push_back({u, w});
    }
    dfs(0, -1); 
    Node *root  = new Node(); 
    Node *root2 = new Node(); 
    int64_t ret = 0; 
    for(int i = 0; i < n; i++) { 
        ret = max(ret, query_max(root, dist[i], LOG));
        insert(root, dist[i], LOG);  
    }
    int64_t ret2 = INT32_MAX;
    insert(root2, 0, LOG); 
    for (int i = 1; i < n; i++) {
        ret2 = min(ret2, query_min(root2, dist[i], LOG));
        insert(root2, dist[i], LOG);
    }
    cout << ret2 << " " << ret << '\n'; 
    return 0; 
}