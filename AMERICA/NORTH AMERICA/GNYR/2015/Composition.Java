import java.lang.*;
import java.util.Scanner;

public class Composition {
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        int tc = scan.nextInt();
        int ProbNum, N, M, K;
        for (int iter = 0; iter < tc; iter++) {
            ProbNum = scan.nextInt();
            N = scan.nextInt();
            M = scan.nextInt();
            K = scan.nextInt();
            long[] dyn = new long[N + 1]; 
            dyn[0] = 1; 
            for(int weight = 1; weight <= N; weight++) 
            for(int c = 0; c <= weight; c++) if((c - M) % K != 0 && c != M) { 
                dyn[weight] += dyn[weight - c]; 
            }
            System.out.printf("%d %d\n", ProbNum, dyn[N]); 
        }
        return; 
    }
}