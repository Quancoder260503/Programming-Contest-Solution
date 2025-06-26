#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

struct node { 
    node* L; 
    node* R; 
    int64_t val;
    node(int64_t _val, node* _L, node* _R) { 
        L = _L, R = _R; 
        val = _val; 
    } 
};

const int maxf = 1e5 + 10; 
int N, Q; 

node* root[maxf];  

node *build(int L, int R) { 
    if(L == R) return new node(0, NULL, NULL);
    int mid = (L + R) / 2; 
    return new node(0, build(L, mid), build(mid + 1, R)); 
}

node *build(int pos, int L, int R, int64_t v, node *pre) { 
    if(pos < L || pos > R) return pre; 
    if(L == R) return new node(pre->val + v, NULL, NULL);
    int mid = (L + R) / 2; 
    node* cc = new node(0, NULL, NULL); 
    cc->L = build(pos, L, mid, v, pre->L);
    cc->R = build(pos, mid + 1, R, v, pre->R);
    cc->val = cc->L->val + cc->R->val; 
    return cc;   
}

int query(int L, int R, node *a, node *b, int k) {
    if(L == R) return L; 
    int mid = (L + R) / 2; 
    int left_size = b->L->val - a->L->val; 
    if(left_size < k) {
       return query(mid + 1, R, a->R, b->R, k - left_size);  
    }
    else { 
       return query(L, mid, a->L, b->L, k); 
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    cin >> N >> Q;
    vector<int>a(N + 1); 
    vector<int>coord; 
    for(int i = 1; i <= N; i++) { 
        cin >> a[i]; 
        coord.push_back(a[i]); 
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    root[0] = build(1, sz(coord)); 
    for(int i = 1; i <= N; i++) {
        int pos = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1; 
        root[i] = build(pos, 1, sz(coord), 1, root[i - 1]); 
    }
    char c;
    for(int iter = 0; iter < Q; iter++) { 
        cin >> c; 
        if(c == 'Q') { 
            int u, v, k; 
            cin >> u >> v >> k; 
            cout << coord[query(1, sz(coord), root[u - 1], root[v], k) - 1] << '\n'; 
        }   
        else { 
            int p; 
            cin >> p;
            int pos = lower_bound(coord.begin(), coord.end(), a[p]) - coord.begin() + 1; 
            root[p] = build(pos, 1, sz(coord), -1, root[p]);
            swap(a[p], a[p + 1]);  
            pos = lower_bound(coord.begin(), coord.end(), a[p]) - coord.begin() + 1; 
            root[p] = build(pos, 1, sz(coord),  1, root[p]);
        }   
    }
    return 0;
}