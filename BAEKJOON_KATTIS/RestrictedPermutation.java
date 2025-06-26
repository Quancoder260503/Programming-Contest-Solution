package PRACTICE.BAEKJOON_KATTIS;

import java.util.*;

public class RestrictedPermutation {
    final static int mod = 1000000007;
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int[] a = new int[N];
        for(int i = 1; i < N; i++) {
            a[i] = stdin.nextInt();
        }
        long[][] dyn = new long[N + 1][N + 1];
        dyn[1][1] = 1;
        for(int i = 2; i <= N; i++) {
            for(int j = 1; j <= i; j++) {
                if(a[i - 1] == 1) {
                    dyn[i][j] = (dyn[i - 1][i - 1] - dyn[i - 1][j - 1] + mod) % mod;
                }
                else {
                    dyn[i][j] = dyn[i - 1][j - 1];
                }
            }
            for(int j = 1; j <= N; j++) {
                dyn[i][j] = (dyn[i][j] + dyn[i][j - 1]) % mod;
            }
        }
        System.out.println(dyn[N][N]);
        stdin.close();
        return;
    }
}
/*
* dyn[i][j] be the number of ways to build the permutation of first i integers
* with the largest integer at position j.
* */