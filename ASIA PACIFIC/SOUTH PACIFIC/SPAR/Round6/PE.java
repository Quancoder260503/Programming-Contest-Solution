import java.util.*;

public class PE {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int[] a = new int[N + 1];
        int[] p = new int[N + 1];
        int[] e = new int[N + 1];
        int[] s = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            s[i] = stdin.nextInt();
            p[i] = stdin.nextInt();
            e[i] = stdin.nextInt();
            a[i] = stdin.nextInt();
        }
        int[][] dyn = new int[N + 1][N + 1];
        for (int i = 1; i < N + 1; i++) {
            for (int j = 0; j < N + 1; j++) {
                dyn[i][j] = -1;
            }
        }
        dyn[0][0] = 0; 
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < i; j++) {
                if (dyn[i - 1][j] != -1) {
                    dyn[i][j] = Math.max(dyn[i][j], dyn[i - 1][j] + s[i] - e[i - 1]);
                }
                if (j > 0 && dyn[i - 1][j - 1] >= a[i - 1]) {
                    dyn[i][j] = Math.max(dyn[i][j], dyn[i - 1][j - 1] + s[i] - p[i - 1] - a[i - 1]);
                }
            }
        }
        int ret = 0;
        for (int i = 0; i <= N; i++) {
            if (dyn[N][i] == -1)
                continue;
            ret = Math.max(ret, i);
            if (dyn[N][i] >= a[N]) {
                ret = Math.max(ret, i + 1);
            }
        }
        System.out.printf("%d\n", ret); 
        stdin.close(); 
        return; 
    }
}
