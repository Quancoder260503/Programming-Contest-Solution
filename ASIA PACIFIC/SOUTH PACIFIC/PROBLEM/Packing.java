import java.util.*;

public class Packing {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int Q = stdin.nextInt();
        for (int iter = 0; iter < Q; iter++) {
            int N = stdin.nextInt();
            int cap_A = stdin.nextInt(), cap_B = stdin.nextInt();
            int[] weight = new int[N + 1];
            int[] value = new int[N + 1];
            for (int i = 1; i <= N; i++) {
                weight[i] = stdin.nextInt();
            }
            for (int i = 1; i <= N; i++) {
                value[i] = stdin.nextInt();
            }
            int[][][] dyn = new int[2][cap_A + 1][cap_B + 1];
            for (int i = 1; i <= N; i++) {
                for (int curr_capA = 0; curr_capA <= cap_A; curr_capA++) {
                    for (int curr_capB = 0; curr_capB <= cap_B; curr_capB++) {
                        if (curr_capA >= weight[i]) {
                            dyn[(i + 1) % 2][curr_capA][curr_capB] = Math.max(dyn[(i + 1) % 2][curr_capA][curr_capB],
                                    dyn[i % 2][curr_capA - weight[i]][curr_capB] + value[i]);
                        }
                        if (curr_capB >= weight[i]) {
                            dyn[(i + 1) % 2][curr_capA][curr_capB] = Math.max(dyn[(i + 1) % 2][curr_capA][curr_capB],
                                    dyn[i % 2][curr_capA][curr_capB - weight[i]] + value[i]);
                        }
                    }
                }
                for (int curr_capA = 0; curr_capA <= cap_A; curr_capA++) {
                    for (int curr_capB = 0; curr_capB <= cap_B; curr_capB++) {
                        dyn[i % 2][curr_capA][curr_capB] = dyn[(i + 1) % 2][curr_capA][curr_capB];
                    }
                }
            }
            int ret = 0;
            for (int curr_capA = 0; curr_capA <= cap_A; curr_capA++) {
                for (int curr_capB = 0; curr_capB <= cap_B; curr_capB++) {
                    ret = Math.max(ret, dyn[N % 2][curr_capA][curr_capB]);
                }
            }
            System.out.format("Problem %d: %d\n", iter + 1, ret); 
        }
        stdin.close();  
        return; 
    }
}
