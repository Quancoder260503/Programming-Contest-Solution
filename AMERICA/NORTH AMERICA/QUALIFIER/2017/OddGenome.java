import java.util.*;

public class OddGenome {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int tc = stdin.nextInt();
        int N; 
        for (int iter = 0; iter < tc; iter++) {
            N = stdin.nextInt();
            int[] a = new int[N];
            for (int i = 0; i < N; i++) {
                a[i] = stdin.nextInt();
            }
            int ret = 0; 
            for(int i = 1; i < N - 1; i++) { 
                if(a[i] != a[i - 1] + 1) { 
                    ret = i; 
                    break; 
                } 
            }
            System.out.printf("%d\n", ret + 1); 
        }
        stdin.close(); 
        return; 
    }
}