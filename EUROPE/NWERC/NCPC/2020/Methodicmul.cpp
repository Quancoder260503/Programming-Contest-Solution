#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e5 + 10
char s[MAXN], t[MAXN]; 
signed main(void)
{
    scanf(" %s", &s); 
    scanf(" %s", &t);
    int n = strlen(s);
    int m = strlen(t);
    int fs = 0;
    int ft = 0;  
    for(int i = 0; i < n; i++)
    {
       fs += (s[i] == '('); 
    }
    for(int i = 0; i < m; i++)
    {
       ft += (t[i] == '('); 
    }
    int len = fs * ft; 
    for(int i = 0; i < len; i++)
    {
       printf("S");
       printf("("); 
    }
    printf("0");
    for(int i = 0; i < len; i++)
    {
         printf(")"); 
    }
    return 0;
}