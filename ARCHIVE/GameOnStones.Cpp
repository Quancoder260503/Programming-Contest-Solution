#include<stdlib.h> 
#include<stdio.h>
long long grundy(long long x){
      return x & 1 ? grundy(x / 2) : x / 2; 
}
int main(void){
    int ntest,n;
    scanf("%d",&ntest); 
    while(ntest--){
          scanf("%d",&n); 
          long long ans = 0;
          for(int i = 0; i < n; i++){
               long long x; scanf("%lld",&x);
                ans = ans xor grundy(x);  
          }
          printf(ans ? "Yes" : "No"); 
    }
    return 0;
}