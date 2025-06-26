#include "bits/stdc++.h"
using namespace std; 
#define MAXN 1001
char arr[MAXN][MAXN];
int len[MAXN];  
signed main(void)
{
     int n; 
     scanf("%d", &n);
     for(int i = 1; i <= n; i++)
     {
         scanf(" %s", &arr[i]); 
         len[i] = strlen(arr[i]);
     } 
     int good = 1; 
     for(int i = 1; i < n; i++)
     {
         good = good & (len[i] < len[i + 1]); 
     }
     if(good)
     {
         puts("impossible");
         return 0; 
     }
     good = 0; 
     for(int i = 1; i <= n; i++)
     { 
        for(int j = 1; j < i; j++)
        {
             if(stoll(arr[i]) < stoll(arr[j]))
             {
                 good = 1; 
                 break; 
             }
             else if(len[i] == len[j])
             { 
                int curr = 0;
                while(curr < len[i])
                {
                     if(arr[j][curr] == '0')
                     {

                     }
                     else if(arr[j][curr] == '1' && curr == 0 && len[i] > 1)
                     {

                     }
                     else
                     {
                         char ch = arr[i][curr];
                         arr[i][curr] = (char) (arr[j][curr] - 1);
                         if (stoll(arr[i]) < stoll(arr[j])) good = 1;
                         else 
                         {
                             arr[i][curr] = ch; 
                         }
                         break;
                     }
                     curr++;
                }
                if(!good)
                {
                    curr = 0;
                    while (curr < len[i])
                    {
                         if(arr[i][curr] == '9')
                         {
                              
                         }
                         else
                         {
                             char ch = arr[j][curr];
                             arr[j][curr] = (char)(arr[i][curr] + 1);
                             if(stoll(arr[i]) < stoll(arr[j])) good = 1;
                             else
                             {
                                     arr[j][curr] = ch;
                             }
                             break;
                         }
                         curr++;
                    }
                }
             }
        }
        if(good)
        {
            break; 
        }
     }
     if(good)
     {
         for(int i = 1; i <= n; i++)
         {
             printf("%s ",arr[i]); 
         }
         printf("\n");
     }
     else
     {
         puts("impossible"); 
     }
     return 0; 
}