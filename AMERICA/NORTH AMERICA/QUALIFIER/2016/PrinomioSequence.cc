#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define f first
#define s second 

int N, M, P; 

int inv[1000005]; 

int64_t add(int64_t a, int64_t b) { 
    return (a + b) % P; 
}

int64_t sub(int64_t a, int64_t b) {
    return (a - b + P) % P; 
}

int Gauss(vector<vector<int64_t>>& A, vector<int64_t>& b, vector<int64_t>& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vector<int> col(m); 
    iota(col.begin(), col.end(), 0);
	for(int i = 0; i < n; i++) {
		int64_t v, bv = 0;
		for(int r = i; r < n; r++) 
        for(int c = i; c < m; c++) { 
			if ((v = abs(A[r][c])) > 0) { 
				br = r, bc = c, bv = v;
            }
        } 
		if (bv == 0) {
			for(int j = i; j < n; j++) if (abs(b[j]) > 0) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for(int j = 0; j < n; j++) { 
            swap(A[j][i], A[j][bc]);
        }
        bv = inv[A[i][i]] % P; 
		for(int j = i + 1; j < n; j++) {
			int64_t fac = A[j][i] * bv % P;
			b[j] = sub(b[j] % P, fac * b[i] % P);
			for(int k = i + 1; k < m; k++)  {
                A[j][k] = sub(A[j][k] % P, fac * A[i][k] % P);
            } 
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = b[i] % P * inv[A[i][i]] % P; 
		x[col[i]] = b[i];
		for(int j = 0; j < i; j++) { 
            b[j] = sub(b[j] % P, A[j][i] * b[i] % P);
        } 
	}
	return rank; // (multiple solutions if rank < m)
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> N >> M >> P;
    vector<vector<int64_t>>A(N * M, vector<int64_t>(N * M, 0)); 
    vector<int64_t>b(N * M); 
    vector<vector<int64_t>>g(N, vector<int64_t>(M)); 
    for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++) { 
        cin >> g[i][j]; 
    }
    for(int i = 1; i <= 2000; i++) { 
        for(int j = 1; j <= 2000; j++) if(i * j % P == 1) { 
            inv[i] = j, inv[j] = i; 
        }
    }
    auto To = [&](int i, int j) { 
        return i * M + j; 
    }; 
    for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++) { 
        b[To(i, j)] = sub(P, g[i][j] % P);
        for(int k = 0; k < N; k++) { 
            A[To(i, j)][To(k, j)] = 1;
        }
        for(int k = 0; k < M; k++) { 
            A[To(i, j)][To(i, k)] = 1; 
        }
        A[To(i, j)][To(i, j)] = 1; 
    }
    vector<int64_t>ret(N * M); 
    if(Gauss(A, b, ret) == -1) { 
        cout << "-1\n";
        return 0; 
    } 
    int sum = 0; 
    for(int i = 0; i < N * M; i++) { 
        sum += ret[i]; 
    }
    cout << sum << '\n'; 
    for(int i = 0; i < N * M; i++) { 
        for(int j = 0; j < ret[i]; j++) { 
            cout << i + 1 << " "; 
        }
    }
    return 0; 
}