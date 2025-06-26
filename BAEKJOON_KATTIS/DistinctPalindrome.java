package PRACTICE.BAEKJOON_KATTIS;

import java.util.*;

public class DistinctPalindrome {
    final static int mod = 1000000007;
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        String S = stdin.next();
        int N = S.length();
        long[][] dyn = new long[N][N];
        for(int i = N - 1; i >= 0; i--) {
            dyn[i][i] = 1;
            for(int j = i + 1; j < N; j++) {
                if(S.charAt(i) == S.charAt(j)) {
                    int left = i + 1, right = j - 1;
                    while(left < j  && S.charAt(left)  != S.charAt(i)) { left++;  }
                    while(right > i && S.charAt(right) != S.charAt(i)) { right--; }
                    if(left == right) {
                        dyn[i][j] = (2 * dyn[i + 1][j - 1] % mod + 1) % mod;
                    }
                    else if(left < right) {
                        dyn[i][j] = (2 * dyn[i + 1][j - 1] % mod - dyn[left + 1][right - 1] + mod) % mod;
                    }
                    else {
                        dyn[i][j] = (2 * dyn[i + 1][j - 1] % mod + 2) % mod;
                    }
                }
                else {
                    dyn[i][j] = (dyn[i + 1][j] + dyn[i][j - 1] - dyn[i + 1][j - 1] + mod) % mod;
                }
            }
        }
        System.out.println(dyn[0][N - 1]);
        stdin.close();
        return;
    }
}
