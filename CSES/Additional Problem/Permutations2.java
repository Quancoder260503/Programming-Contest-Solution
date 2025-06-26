import java.util.*;

public class Permutations2 {
    final static int mod = 1000000007;
    static long[][][] dyn; 
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        dyn = new long[N + 1][N + 1][3];
        dyn[0][0][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (j + 1 <= N) {
                    dyn[i][j][0] += (dyn[i - 1][j + 1][0] % mod * j % mod * (j + 1) % mod +
                            dyn[i - 1][j + 1][1] % mod * j % mod * j % mod +
                            dyn[i - 1][j + 1][2] % mod * j % mod * (j - 1) % mod) % mod;
                }
                dyn[i][j][1] = (dyn[i - 1][j][0] % mod * (2 * j) % mod +
                        dyn[i - 1][j][1] % mod * (2 * j - 1) % mod +
                        dyn[i - 1][j][2] % mod * (2 * j - 2) % mod) % mod;
                dyn[i][j][2] = (dyn[i - 1][j - 1][0] + dyn[i - 1][j - 1][1] + dyn[i - 1][j - 1][2]) % mod;
            }
        }
        long ret = (dyn[N][1][0] + dyn[N][1][1] + dyn[N][1][2]) % mod; 
        System.out.format("%d\n", ret); 
        stdin.close(); 
        return; 
    }
}

/*
 * dyn[i][j][k] = {number of ways to arrange the first ith intergers such that there are j connected components
 * and the ith element has k borders.}
 * dyn[i][j][0] = dyn[i - 1][j + 1][0] * j * (j + 1) + dyn[i - 1][j + 1][1] * j * j + dyn[i - 1][j + 1][2]
 *               
 * 
 */