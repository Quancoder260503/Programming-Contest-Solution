package PRACTICE.BAEKJOON_KATTIS;

import java.util.*;

public class DistinctNeighbor {
    final static int mod = 1000000007;
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int[] freq = new int[N + 1];
        for(int i = 0; i < N; i++) {
            int x = stdin.nextInt();
            freq[x]++;
        }
        long[][] Comb = new long[N + 1][N + 1];
        long[][] dyn = new long[N + 1][N + 1];
        Comb[0][0] = 1;
        for(int i = 1; i <= N; i++) {
            for (int j = 0; j <= i; j++) {
                Comb[i][j] = (Comb[i - 1][j] + (j > 0 ? Comb[i - 1][j - 1] : 0)) % mod;
            }
        }
        int[] a = new int[N + 1];
        int size = 0;
        for(int i = 1; i <= N; i++) {
            if(freq[i] == 0) continue;
            a[size++] = i;
        }
        dyn[0][freq[a[0]] - 1] = 1;
        N = size;
        size = freq[a[0]];
        for(int i = 1; i < N; i++) {
            for(int special_pair = 0; special_pair < size; special_pair++) {
                for(int choose = 1; choose <= Math.min(freq[a[i]], size + 1) ; choose++) {
                    for(int special = 0; special <= Math.min(special_pair, choose); special++) {
                        int next_j = special_pair - special + freq[a[i]] - choose;
                        dyn[i][next_j] += dyn[i - 1][special_pair] % mod * Comb[freq[a[i]] - 1][choose - 1] % mod *
                                          Comb[size + 1 - special_pair][choose - special] % mod * Comb[special_pair][special] % mod;
                        dyn[i][next_j] %= mod;
                    }
                }
            }
            size += freq[a[i]];
        }
        System.out.println(dyn[N - 1][0]);
        stdin.close();
        return;
    }
}
/*
* dyn[i][j] = { number of ways to build the permutation from the first i integers
*               and there are j pairs of equal adjacent element }
*
* Let k be the next state (k is the number of equals pair with equal adjacent element,
* L be the number of elements that have been filled,
* there are L + 1 gaps with j of them have equal adjacent pairs.
* we are choosing y of them choose filled at least one element,
*
* say we are going to insert X elements freq[i] into the k gaps and y of them is special
* The number of options is Comb(freq[i] - 1, k - 1).
* dyn[i][j - y + (freq[i] - k)] = Comb(freq[i] - 1, k - 1) * dyn[i - 1][j].
* */
