#include "bits/stdc++.h"

using namespace std;

const double PI = acos(-1); 

double get_ang(double ang)
{
    if(ang < 0)  ang += PI; 
    if(ang > PI) ang -= PI;
    return ang;  
}

int main(void)
{
    int N;
    while(cin >> N)
    {
        vector<double>rx(N), ry(N); 
        for(int i = 0; i < N; i++) cin >> rx[i] >> ry[i]; 
        vector<vector<double>>angs;
        vector<vector<int>>nxts; 
        for(int i = 0; i < N; i++) 
        {
            vector<int>nxt(N);
            vector<double>ang(N); 
            vector<pair<double, int>>arr; 
            //arr.push_back({0, i}); 
            for(int j = 0; j < N; j++) if(i != j)
            {
                int dx = rx[j] - rx[i];
                int dy = ry[j] - ry[i];
                if(dy < 0 || (dy == 0 && dx < 0))
                {
                    dx = -dx; 
                    dy = -dy;
                }
                arr.push_back({atan2(dy, dx), j}); 
            }
            sort(arr.begin(), arr.end()); 
            for(int j = 0; j < arr.size(); j++)
            {
                nxt[arr[j].second] = arr[(j + 1) % arr.size()].second;
                ang[arr[j].second] = get_ang(arr[(j + 1) % arr.size()].first - arr[j].first);  
            }
            angs.push_back(ang); 
            nxts.push_back(nxt); 
        }
        vector<vector<int>>vis(N, vector<int>(N)); 
        int ret = 0; 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) if(i != j && !vis[i][j])
        {
            vector<int>ctr(N); 
            int ati = i; 
            int atj = j;
            double totang = 0;
            while(true)
            {
                ctr[ati]++; 
                vis[ati][atj] = 1; 
                int atk = nxts[ati][atj]; 
                totang += angs[ati][atj]; 
                atj = ati;
                ati = atk; 
                if(ati == i && atj == j && totang >= 1.5 * PI) break; 
            }
            for(int k = 0; k < N; k++) ret = max(ret, ctr[k]); 
        }
        cout << ret << '\n'; 
    }
    return 0;
}