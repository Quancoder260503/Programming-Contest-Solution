#include "bits/stdc++.h"

using namespace std;

const int maxf = (1 << 22); 

int aux[maxf], vis[maxf]; 
vector<vector<int>>ret; 
vector<int>arr, ctr;
int N; 

void f(int L, int R)
{
    if(L + 1 == R) 
    {
        if(arr[L] == 0) ret.push_back(ctr); 
        return; 
    }
    int sz = R - L; 
    int diff = arr[R - 1] - arr[R - 2]; 
    for(int i = 0; i < sz; i++) vis[i] = false; 
    int it = 0;
    for(int i = 0, j = 1; i < sz; i++)
    {
        if(vis[i]) continue; 
        j = max(j, i + 1); 
        int val = arr[L + i]; 
        while(j < sz && val + diff > arr[L + j]) j++;
        if(j >= sz || val + diff < arr[L + j]) return; 
        vis[j] = true; 
        arr[L + it] = val; 
        aux[it++] = val + diff; 
        j++; 
    }
    for(int i = 0; i < it; i++) arr[L + it + i] = aux[i]; 
    ctr.push_back(diff);
    f(L, L + it); 
    ctr.pop_back(); 
    ctr.push_back(-diff);
    f(L + it, R); 
    ctr.pop_back();  
    return; 
}

int main(void)
{
    cin >> N; 
    N = (1 << N); 
    arr.resize(N); 
    for(int i = 0; i < N; i++) cin >> arr[i]; 
    sort(arr.begin(), arr.end()); 
    f(0, N);
    for(auto &v : ret) sort(v.begin(), v.end());
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end()); 
    for(int i = 0; i < ret.size(); i++)
    {
        for(auto v : ret[i]) cout << v << " "; 
        cout << '\n'; 
    }
    return 0;
}