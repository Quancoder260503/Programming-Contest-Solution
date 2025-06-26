#include "bits/stdc++.h"
using namespace std; 
char s[27]; 
int n; 
int a[27]; 
void go(int pos)
{
    if(pos == n)
    {
        for(int i = 0; i <= n / 2; i++)
        {
             printf("%d", a[i]); 
        }
        printf("\n"); 
        exit(0);
    }
    for(int digit = 0; digit <= 9; digit++)
    {
        int tot = 0;
        a[pos] = digit;  
        if(pos > n / 2 && digit != 0) return;
        for(int j = 0; j <= pos; j++)
        { 
            if(pos - j > 1 + n / 2) continue; 
            tot += a[j] * a[pos - j];
            tot = tot % 10; 
        }
        if(s[pos] - '0' == tot)
        {
            go(pos + 1); 
        }
    }
    return; 
}
signed main(void)
{
    scanf(" %s", &s); 
    n = strlen(s); 
    go(0); 
    puts("-1"); 
    return 0; 
}