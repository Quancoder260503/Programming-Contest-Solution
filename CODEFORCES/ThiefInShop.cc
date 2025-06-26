#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 1; 
int64_t dyn[maxf]; 
int64_t arr[maxf]; 


int main(void)
{
    int N, K;
    cin >> N >> K; 
    for(int i = 1; i <= N; i++)
    {
        cin >> arr[i]; 
    }
    memset(dyn, 63, sizeof(dyn)); 
    dyn[0] = 0; 
    int64_t c = *min_element(arr + 1, arr + N + 1); 
    for(int i = 1; i <= N; i++) arr[i] = arr[i] - c; 
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j + arr[i] < maxf; j++)
        {
           dyn[j + arr[i]] = min(dyn[j + arr[i]], dyn[j] + 1); 
        }
    }
    for(int j = 0; j < maxf; j++) if(dyn[j] <= K)
    {
        cout << j + K * c << " "; 
    }
    return 0;
}
