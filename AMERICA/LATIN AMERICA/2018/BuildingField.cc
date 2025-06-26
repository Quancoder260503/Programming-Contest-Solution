#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10; 
int64_t arr[maxf], prefix[maxf]; 

int main(void)
{
    int N; 
    while(cin >> N)
    {
        int64_t sum = 0; 
        for(int i = 1; i <= N; i++) 
        {
            cin >> arr[i]; 
            prefix[i] = arr[i] + prefix[i - 1]; 
            sum += arr[i]; 
        }
        int ret = 0, ptr = 1;  
        int64_t curr = 0; 
        for(int i = 1; i <= N; i++)
        {
            while(ptr < N && 2 * (prefix[ptr] - curr) < sum) ptr++; 
            if(ptr < N && 2 * (prefix[ptr] - curr) == sum) ret++; 
            curr = prefix[i]; 
        }
        cout << (ret > 1 ? 'Y' : 'N') << '\n'; 
    }
    return 0;
}