#include "bits/stdc++.h"
using namespace std;
#define MAXN 55
#define x first
#define y second
using pii = pair<int, int>;
pii A[MAXN]; 
signed main(void)
{
    int n;
    cin >> n;
    int Alice; 
    int Bob; 
    Alice = Bob = 0;
    for(int i = 1; i <= n; i++)
    {
         int Acurr, Bcurr;
         scanf("%d-%d", &Acurr, &Bcurr);
         int tot = Acurr + Bcurr;
         if(tot % 4 == 1 || tot % 4 == 2)
         {
             swap(Acurr,Bcurr); 
         }
         if (Acurr < Alice || Bcurr < Bob || (Acurr == 11 && Bcurr == 11))
         {
             printf("error %d", i);
             return 0;
         }
         if(Alice == 11 || Bob == 11)
         {
            if(Alice != Acurr || Bob != Bcurr)
            {
                 printf("error %d",i); 
                 return 0;
            }
         }
         Alice = Acurr;
         Bob = Bcurr;
    }
    printf("ok\n"); 
    return 0;
}