#include <bits/stdc++.h> 

using namespace std; 

const int OFFSET = 5002; 

double dp[2 * OFFSET][OFFSET]; 

int main() { 
 for(int i = 0; i < 2 * OFFSET; i++) { 
  for(int j = 0; j < OFFSET; j++) { 
   dp[i][j] = -1; 
  } 
 } 
 int N, K; 
 cin >> N >> K; 
 vector<double>Prob(N); 
 for(int i = 0; i < N; i++) { 
  cin >> Prob[i]; 
 } 
 sort(Prob.rbegin(), Prob.rend()); 
 function<double(int, int)> memo = [&](int n, int k) -> double { 
  if(n == -1) return k == 0; 
  if(k + OFFSET >= 2 * OFFSET) return 0; 
  double &ret = dp[k + OFFSET][n]; 
  if(ret >= 0) return ret;
  ret = Prob[n] * memo(n - 1, k - 1) + (1. - Prob[n]) * memo(n - 1, k + 1); 
  return ret; 
 }; 
 vector<double>ret(N);
 double ans = 0; 
 for(int pos = K - 1; pos < N; pos++) { 
  for(int num = K; num <= pos + 1; num++) { 
   ret[pos] += memo(pos, num); 
  }
  ans = max(ans, ret[pos]); 
 }
 cout << fixed << setprecision(10) << ans << '\n'; 
 return 0;
}

/**
 * #include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define MAXN 10005
#define inf 1e9 
double dp[MAXN][MAXN];
double A[MAXN];  
int n,k; 
double s[MAXN]; 
signed main(void)
{
     scanf("%d%d",&n,&k);
     for(int i = 1; i <= n; i++)
     {
         scanf("%lf",&A[i]); 
     }
     sort(A + 1, A + n + 1);
     reverse(A + 1, A + n + 1); 
     int score = n; 
     dp[0][score] = 1.0; 
     for(int i = 1; i <= n; i++)
     { 
         for(int j = score - i - 1; j <= score + i + 1; j++)
         { 
             dp[i][j] = A[i] * dp[i - 1][j - 1] + (1.0 - A[i]) * dp[i - 1][j + 1];
         }
         for(int j = score + k; j <= score + n; j++)
         {
             s[i] += dp[i][j]; 
         }
     }
     double ans = 0;  
     for(int i = k; i <= n; i++)
     {
         ans = max(ans, s[i]);
     }
     printf("%lf\n",ans); 
     return 0; 
}
 * 
 */