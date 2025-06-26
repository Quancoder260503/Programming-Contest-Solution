#include "bits/stdc++.h"

using namespace std; 

const int THRESHOLD = 150000; 
const int oo = 1'000'000'000; 

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
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int N; 
    cin >> N;
    vector<int>h(N); 
    for(int i = 0; i < N; i++) { 
        cin >> h[i]; 
    }
    vector<int>peaks; 
    for(int i = 0; i < N; i++) { 
        if(i == 0     && i + 1 < N && h[i] > h[i + 1]) { peaks.push_back(i); }
        if(i == N - 1 && i     > 0 && h[i] > h[i - 1]) { peaks.push_back(i); }
        else if(h[i - 1] < h[i] && h[i] > h[i + 1]) { 
            peaks.push_back(i); 
        }
    }
    Tree tree(N);
    for(int i = 0; i < N; i++) { 
        tree.update(i, h[i]); 
    } 
    stack<int>stk; 
    vector<int>dist(N, -1); 
    for(int i = 0; i < peaks.size(); i++) { 
        while(stk.size() && h[stk.top()] <= h[peaks[i]]) { 
            stk.pop(); 
        }
        if(stk.size()) { 
            int c = tree.query(stk.top() + 1, peaks[i]); 
            dist[peaks[i]] = h[peaks[i]] - c; 
        }
        else { 
            dist[peaks[i]] = h[peaks[i]]; 
        }
        stk.push(peaks[i]); 
    }
    while(stk.size()) { stk.pop(); }
    for(int i = int(peaks.size()) - 1; i >= 0; i--) { 
        while(stk.size() && h[stk.top()] <= h[peaks[i]]) { 
            stk.pop(); 
        }
        if(stk.size()) { 
            int c = tree.query(peaks[i] + 1, stk.top()); 
            dist[peaks[i]] = min(dist[peaks[i]], h[peaks[i]] - c); 
        }
        else { 
            dist[peaks[i]] = min(h[peaks[i]], dist[peaks[i]]); 
        }
        stk.push(peaks[i]); 
    }
    for(int i = 0; i < N; i++) if(dist[i] >= THRESHOLD){
        cout << i + 1 << " ";  
    }
    cout << '\n'; 
    return 0;
}