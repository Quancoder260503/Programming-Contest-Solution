#include <stdlib.h> 
#include <stdio.h>
int main(void){
    int ntest; 
    scanf("%d",&ntest);
    for(int i = 0; i < ntest; i++){
          int n; scanf("%d",&n);
          long long ans = 0; 
          for(int i = 0; i < n; i++){
               long long x; scanf("%lld",&x);
               ans = ans xor (x % 4); 
          }
          printf(ans ? "first" : "second" );
          printf("\n"); 
    }
    return 0;
}
