#include  "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 5
typedef struct 
{
    double flowa, flowb, temp;  
} tap;
bool cmp(const tap &a, const tap &b)
{
     return a.temp < b.temp; 
}
tap arr[MAXN]; 
int n, q; 
signed main(void)
{
    scanf("%d", &n); 
    double tota = 0; 
    double totb = 0;
    double tott = 0;  
    for(int i = 1; i <= n; i++)
    {
         scanf("%lf %lf %lf", &arr[i].temp, &arr[i].flowa, &arr[i].flowb); 
         tota += arr[i].flowa; 
         totb += arr[i].flowb;
         tott += arr[i].temp * arr[i].flowa;  
    }
    sort(arr + 1, arr + n + 1, cmp); 
    scanf("%d", &q); 
    for(int j = 0; j < q; j++)
    {
        double f, t; 
        scanf("%lf %lf", &t, &f); 
        if(f < tota || f > totb)
        {
             puts("no");
             continue; 
        }
        double curr = f - tota; 
        double curra = 0;
        double currb = 0;
        for(int i = 1; i <= n; i++)
        {
              if(curr >= arr[i].flowb - arr[i].flowa)
              {
                  curr = curr - (arr[i].flowb - arr[i].flowa);
                  curra += arr[i].temp * (arr[i].flowb - arr[i].flowa);
              }
              else
              {
                 curra += arr[i].temp * curr; 
                 break; 
              }
        }
        curr = f - tota; 
        for(int i = n; i > 0; i--)
        {
              if (curr >= arr[i].flowb - arr[i].flowa)
              {
                 curr = curr - (arr[i].flowb - arr[i].flowa);
                 currb += arr[i].temp * (arr[i].flowb - arr[i].flowa);
              }
              else
              {
                 currb += arr[i].temp * curr;
                 break;
              }
        }
        curra = (curra + tott) / f; 
        currb = (currb + tott) / f; 
        if(curra <= t && t <= currb)
        { 
           puts("yes");    
        }
        else
        {
            puts("no"); 
        }
    }
    return 0; 
}