package PRACTICE.ATCODER;
import java.util.*;

public class LCS {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        String Sa = stdin.next();
        String Sb = stdin.next();
        int Na = Sa.length(), Nb = Sb.length();
        int[][] dyn = new int[Na + 1][Nb + 1];
        for (int i = 1; i <= Na; i++) {
            for (int j = 1; j <= Nb; j++) {
                if (Sa.charAt(i - 1) == Sb.charAt(j - 1)) {
                    dyn[i][j] = 1 + dyn[i - 1][j - 1];
                }
                dyn[i][j] = Math.max(dyn[i - 1][j], dyn[i][j]);
                dyn[i][j] = Math.max(dyn[i][j - 1], dyn[i][j]);
            }
        }
    ///    System.out.printf("%d\n", dyn[Na][Nb]);
        String ret = "";
        int nA = Na, nB = Nb;
        while (nA > 0 && nB > 0) {
            if (dyn[nA][nB] == dyn[nA - 1][nB]) {
                nA = nA - 1;
            } else if (dyn[nA][nB] == dyn[nA][nB - 1]) {
                nB = nB - 1;
            } else if (dyn[nA][nB] == dyn[nA - 1][nB - 1] + 1) {
                ret = Sa.charAt(nA - 1) + ret;
                nA = nA - 1;
                nB = nB - 1;
            }
        }
        System.out.println(ret); 
        stdin.close(); 
        return; 
    }
}
