#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 

struct Tree {
	typedef int T;
	static constexpr T unit = int(1e9);
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m; 
    cin >> n;
    vector<tuple<int, int, int>>slot;
    for(int i = 0, x, y; i < n; i++) { 
        cin >> x >> y; 
        slot.push_back({x, i, y}); 
    }
    cin >> m;
    for(int i = 0, x, y; i < m; i++) { 
        cin >> x >> y; 
        slot.push_back({x, -1, y}); 
    }
    Tree tree(maxf); 
    sort(slot.rbegin(), slot.rend()); 
    int64_t ret = 0; 
    for(auto [x, idx, y] : slot) { 
        if(idx == -1) {  
            ret += tree.query(0, y + 1); 
        }
        else { 
            tree.update(y, idx + 1); 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}