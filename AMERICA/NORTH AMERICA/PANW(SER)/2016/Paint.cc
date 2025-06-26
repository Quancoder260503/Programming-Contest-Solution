#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1e6 + 10; 

struct node { 
    int64_t l, r; 
} a[maxf]; 

int64_t N, K, dyn[maxf]; 

int cmp(const node a, const node b) { 
    return a.r == b.r ? a.l > b.l : a.r < b.r;
}
int cmp2(node a, node b) { 
    return a.r < b.l; 
}

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> N >> K; 
    for(int i = 1; i <= K; i++) { 
        cin >> a[i].l >> a[i].r;
    }
    sort(a + 1, a + K + 1, cmp); 
    for(int i = 1; i <= K; i++) { 
        int pos = lower_bound(a + 1, a + K + 1, a[i], cmp2) - a - 1; 
        dyn[i] = max(dyn[i - 1], dyn[pos] + a[i].r - a[i].l + 1);
    }
    cout << N - dyn[K] << '\n'; 
    return 0; 
}