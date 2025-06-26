#include "bits/stdc++.h"

using namespace std; 

struct Tree {
	typedef int64_t T;
	static constexpr T unit = LLONG_MAX / 2;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val) {
        pos += n; 
        s[pos] = min(val, s[pos]); 
		for (; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};


int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N, Q; 
    cin >> N >> Q; 
    Tree tree(N);
    int64_t x, l, r;  
    vector<int64_t>a(N); 
    for(int i = 0; i < N; i++) { 
        cin >> a[i]; 
        tree.update(i, a[i]); 
    }
    for(int iter = 0; iter < Q; iter++) { 
        cin >> x >> l >> r;
        --l, --r; 
        while(l <= r) {
            int ql = l, qr = r, ret = -1; 
            while(ql <= qr) { 
                int mid = (ql + qr) / 2; 
                if(tree.query(l, mid + 1) <= x) { 
                    qr = mid - 1; 
                    ret = mid; 
                }
                else { 
                    ql = mid + 1; 
                }
            }
            if(ret == -1) break; 
            x %= a[ret]; 
            l = ret + 1; 
        }
        cout << x << '\n';  
    }
    return 0; 
}