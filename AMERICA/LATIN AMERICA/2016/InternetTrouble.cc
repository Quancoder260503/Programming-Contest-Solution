#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int maxf = 6e3 + 2;
const int64_t oo = LLONG_MAX / 2; 

int64_t dyn[maxf][maxf], prefix[maxf], prefix2[maxf], cost[maxf][maxf], opt[maxf][maxf];
int N, B, C; 

int64_t F(int i, int j, int mid) {
    return   2LL * mid * prefix[mid] - 1LL * mid * (prefix[j] + prefix[i - 1])
             + prefix2[j] + prefix2[i - 1] - 2 * prefix2[mid]; 
}

int main(void) {
    scanf("%d %d %d", &N, &B, &C); 
    for(int i = 1, x; i <= N; i++) { 
        scanf("%d", &x); 
        prefix[i]  = prefix[i - 1] + 1LL * x; 
        prefix2[i] = prefix2[i - 1] + 1LL * i * x;
    }
    for(int i = 1; i <= N; i++) { 
        dyn[0][i] = oo / 2;
    }
    for(int i = 1; i <= N; i++)
    for(int j = 0; j < i; j++) { 
        dyn[i][j] = oo / 2; 
    } 
    for(int i = 1; i <= N; i++) { 
        int opt = i; 
        for(int j = i; j <= N; j++) { 
            while(opt < j && F(i, j, opt) >= F(i, j, opt + 1)) opt++;
            cost[i][j] = F(i, j, opt);  
        }
    } 
    for(int i = 1; i <= N; i++) { 
        opt[i][i] = i; 
    }
    for(int i = 1; i < N; i++) 
    for(int j = i + 1; j <= N; j++) {
        dyn[j - i][j] = oo / 2;  
        for(int k = opt[j - i][j - 1]; k <= opt[j - i + 1][j]; k++) if(dyn[j - i][j] > cost[k][j] + dyn[j - i - 1][k - 1]) {
          dyn[j - i][j] = cost[k][j] + dyn[j - i - 1][k - 1];    
          opt[j - i][j] = k; 
        }
    }
    for(int i = 1; i <= N; i++) { 
        printf("%lld ", 1LL * B * i + 1LL * C * dyn[i][N]);  
    }   
    return 0;
}