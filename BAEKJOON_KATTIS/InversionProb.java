package PRACTICE.BAEKJOON_KATTIS;

import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.*;

public class InversionProb {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        DecimalFormat decformat = new DecimalFormat();
        decformat.setRoundingMode(RoundingMode.HALF_EVEN);
        int N = stdin.nextInt();
        long[] r = new long[N];
        for (int i = 0; i < N; i++) {
            r[i] = stdin.nextLong();
        }
        Double ret = 0.0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (r[j] < r[i]) {
                    ret += 1.0 * (r[j] * 0.5 - 0.5) / r[i];
                } else {
                    ret += 1.0 * (r[j] - 0.5 * r[i] - 0.5) / r[j];
                }
            }
        }
        System.out.format("%.6f\n", ret); 
        stdin.close();
        return;
    }
} 