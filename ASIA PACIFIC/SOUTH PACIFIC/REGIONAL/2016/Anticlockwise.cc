#include "bits/stdc++.h"

using namespace std; 

#define x first
#define y second 

const int maxf = 1e5;
map<int64_t, int64_t>ord; 

pair<int64_t, int64_t>f(int64_t o, int64_t a)
{
    for(int i = 1; i <= maxf; i += 2)
    {
        int64_t b = 1LL * i * i; 
        if(b == a) return {ord[o] - ord[a], ord[o] - ord[a]}; 
        else if(b > a)
        {
            if (b - i + 1 < a)
            {
                return {ord[o] - ord[b], ord[o] - ord[b] + b - a};
            }
            else if(b - 2 * i + 2 < a)
            {
                return {ord[o] - ord[b] + (b - i + 1) - a , ord[o] - ord[b] + (i - 1)}; 
            }
            else if(b - 3 * i + 3 < a)
            {
                return {ord[o] - ord[b] + i - 1, ord[o] - ord[b] + a - (b - 3 * i + 3)}; 
            }
            else if(b - 4 * i + 4 < a)
            {
                return {ord[o] - ord[b] + a - (b - 4 * i + 4), ord[o] - ord[b]}; 
            }
        }
    }
    return {}; 
}

void init(void)
{
    int ctr = 0; 
    for(int i = 1; i <= maxf; i += 2) ord[1LL * i * i] = ctr++; 
    return; 
}

int main(void)
{
    init(); 
    int64_t a, b; 
    cin >> a >> b;
    auto da = f(1LL * maxf * maxf, a);
    auto db = f(1LL * maxf * maxf, b); 
    //cout << da.x << " " << da.y << " " << db.x << " " << db.y << '\n'; 
    int64_t ret = abs(da.x - db.x) + abs(da.y - db.y); 
    cout << ret << '\n'; 
    return 0; 
}