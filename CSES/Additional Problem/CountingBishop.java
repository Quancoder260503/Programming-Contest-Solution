import java.util.*;

public class CountingBishop {
    final static int mod = 1000000007;
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int K = stdin.nextInt();
        if(K > 2 * N - 1) {
            System.out.println(0);
            return; 
        }
        long[][] dyn = new long[2 * N][K + 1];
        for(int i = 0; i < 2 * N; i++) {
            dyn[i][0] = 1;
        }
        dyn[1][1] = 1;
        for(int i = 2; i < 2 * N; i++) {
            for(int j = 1; j <= K; j++) {
                int square = (i % 2 == 1 ? i / 4 * 2 + 1 : (i - 1) / 4 * 2 + 2);
                dyn[i][j] = (dyn[i - 2][j] + dyn[i - 2][j - 1] % mod * (square - j + 1) % mod) % mod;
            }
        }
        long ret = 0;
        for(int i = 0; i <= K; i++) {
            ret += dyn[2 * N - 1][i] % mod * dyn[2 * N - 2][K - i] % mod;
            ret %= mod;
        }
        System.out.println(ret);
        stdin.close();
        return;
    }
}
