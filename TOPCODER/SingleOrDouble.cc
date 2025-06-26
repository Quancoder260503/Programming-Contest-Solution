#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

class SingleOrDouble {
public:
    double probAlice(int N, int D, int A, int B) {
        int sum = N * D; 
        vector<vector<double>>dyn(N + 1, vector<double>(sum + 1)); 
        dyn[0][0] = 1; 
        for(int i = 1; i <= N; i++)
        for(int j = 0; j <= sum; j++)
        for(int face = 1; face <= min(j, D); face++) { 
            dyn[i][j] += dyn[i - 1][j - face] / D; 
        }
        double pa = dyn[N][A], pb = dyn[N][B]; 
        return (pa + pb * pa) / (pa + pa * pb + pb * pb); 
   }; 
};