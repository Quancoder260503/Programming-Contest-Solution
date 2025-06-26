#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
#define M 102
int n, p;  
double A[MAXN]; 
double P[MAXN]; 
double dp[M][M][M]; 
char s[M][M]; 
signed main(void)
{
     scanf("%d%d", &n, &p);
     for(int i = 1; i < n; i++)
     {
         scanf("%lf", A + i); 
     }
     for(int i = 1; i <= p; i++)
     {
         scanf("%lf", P + i); 
     }
     for(int i = 1; i < n; i++)
     {
         for(int j = 1; j <= p; j++)
         {
             scanf(" %c", &s[i][j]); 
         }
     }
     for(int k = 1; k < n; k++)
     {
         dp[k][0][0] = 1.0;
         for(int i = 1; i <= p; i++)
         {
             for(int j = 0; j <= i; j++)
             {
                  if(s[k][i] == '?')
                  {
                     if(j > 0) dp[k][i][j] = dp[k][i - 1][j - 1] * A[k] * P[i];
                     dp[k][i][j] += dp[k][i - 1][j] * (1.0 - A[k] * P[i]);
                  }
                  else if(s[k][i] == '-')
                  {
                     dp[k][i][j] = dp[k][i - 1][j];
                  }
                  else
                  {
                     if(j > 0) dp[k][i][j] = dp[k][i - 1][j - 1];
                  }
             }
         }
     }
     int solved = 0;
     for(int i = 1; i <= p; i++)
     {
         char ch; scanf(" %c", &ch); 
         solved += (ch == 'X'); 
     }
     double ans = 1.0 ; 
     for(int k = 1; k < n; k++)
     {
         double tot = 0; 
         for(int i = 0; i <= solved; i++)
         {
             tot += dp[k][p][i]; 
         }
         ans = ans * tot;
     }
     printf("%lf\n",ans); 
     return 0; 
}
/* Let f(i, j) be the probability that the kth players get j th solved problems after the first ith problems */
/* Let f(i, j) = f(i - 1, j + 1) * s * d + f(i - 1, j) * (1 - s * d)  for S[i] = '?'
       f(i, j) = f(i - 1, j - 1)  for S[i] = 'X'
       f(i, j) = f(i - 1, j) for S[i] = '-'
*/