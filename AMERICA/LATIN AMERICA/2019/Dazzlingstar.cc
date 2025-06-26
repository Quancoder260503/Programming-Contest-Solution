#include "bits/stdc++.h"

#define double long double 
using namespace std;

const double PI = acos(-1); 
const int maxf = 2e5 + 10;
pair<double, double>P[maxf]; 
int B[maxf];

double fixang(int dx, int dy)
{
    if(!dy) return (dx > 0 ? 0 : PI); 
    if(!dx) return (dy > 0 ? PI / 2 : -PI / 2); 
    return atan(1.0 * dy / dx) + (dx <= 0) * PI; 
}

int main(void)
{
    int N; 
    while(cin >> N)
    { 
        for(int i = 1; i <= N; i++) cin >> P[i].first >> P[i].second >> B[i]; 
        vector<int>ord(N); 
        iota(ord.begin(), ord.end(), 1);
        auto cmp = [&](int a, int b){return B[a] < B[b]; }; 
        sort(ord.begin(), ord.end(), cmp); 
        vector<double>angs; 
        for(int i = 0; i < ord.size(); i++) for(int j = 0; j < i; j++)
        {
            int u = ord[i];
            int v = ord[j]; 
            if(B[v] < B[u])
            {
                int dx = P[u].first - P[v].first;
                int dy = P[u].second - P[v].second; 
                angs.push_back(fixang(dx, dy));
            }
        }
        sort(angs.begin(), angs.end()); 
        auto ret = [&](void)
        {
            if(angs.size() < 2) return true;
            double pre = angs.back() - 2 * PI; 
            for(int i = 0; i < angs.size(); i++)
            {
                if(PI - angs[i] + pre <= 1e-9) return true; 
                pre = angs[i]; 
            }
            return false; 
        }; 
        cout << (ret() ? 'Y' : 'N') << '\n'; 
    }
    return 0;
}