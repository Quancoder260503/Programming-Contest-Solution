#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 1; 
const int THRES = 100; 
const double oo = 1e50; 
const double eps = 1e-6;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N; 
    double M; 
    cin >> N;  
    vector<int>ry(N), rx(N);
    vector<double>T(N), P(N + 1); 
    for(int i = 0; i < N; i++) { 
        cin >> rx[i] >> ry[i] >> T[i]; 
    }
    cin >> M;
    P[0] = 1; 
    for(int i = 1; i < N + 1; i++) { 
        P[i] = P[i - 1] * M; 
    } 
    auto F = [&](double velocity) { 
        vector<vector<double>>dyn(N, vector<double>((1 << N), oo)); 
        for(int i = 0; i < N; i++) { 
            double dist = hypot(rx[i], ry[i]); 
            if(dist / velocity < T[i]) { 
                dyn[i][(1 << i)] = dist / velocity; 
            }
        }
        for(int mask = 0; mask < (1 << N); mask++) { 
            for(int i = 0; i < N; i++) if((mask & (1 << i))) {
                for(int j = 0; j < N; j++) if(!(mask & (1 << j))) { 
                    double dist = hypot(rx[i] - rx[j], ry[i] - ry[j]); 
                    int count_mask = __builtin_popcount(mask); 
                    if(dyn[i][mask] + dist / (velocity * P[count_mask]) <  T[j]) { 
                        dyn[j][mask | (1 << j)] = min(dyn[j][mask | (1 << j)], 
                                                      dyn[i][mask] + dist / (velocity * P[count_mask])); 
                    }
                } 
            }
        }
        for(int i = 0; i < N; i++) { 
            if(dyn[i][(1 << N) - 1] < oo) return true; 
        }
        return false; 
    };
    double lo = eps; 
    double hi = 1e20 - eps; 
    for(int iter = 0; iter < THRES; iter++) { 
        double mid = (lo + hi) / 2; 
        if(F(mid)) hi = mid; 
        else       lo = mid; 
    }
    cout << fixed << setprecision(20) << lo << '\n'; 
    return 0;
}