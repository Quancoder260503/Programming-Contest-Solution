package PRACTICE.ATCODER;
import java.util.*;

public class LongestPath {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt(), M = stdin.nextInt();
        ArrayList<Integer>[] adj  = new ArrayList[N];
        ArrayList<Integer>[] radj = new ArrayList[N];  
        int[] deg = new int[N]; 
        for (int i = 0; i < N; i++) {
            adj[i]  = new ArrayList<>();
            radj[i] = new ArrayList<>(); 
        }
        for (int i = 0, u, v; i < M; i++) {
            u = stdin.nextInt() - 1;
            v = stdin.nextInt() - 1;
            adj[u].add(v);
            radj[v].add(u); 
            deg[v]++;
        }
        LinkedList<Integer> q = new LinkedList<Integer>();
        ArrayList<Integer>ord = new ArrayList<Integer>();
        for (int i = 0; i < N; i++) {
            if (deg[i] == 0) {
                ord.add(i); 
                q.push(i);
            }
        }
        while (q.size() > 0) {
            int u = q.pollFirst();
            for (Integer v : (ArrayList<Integer>) adj[u]) {
                deg[v]--;
                if (deg[v] == 0) {
                    ord.add(v);
                    q.push(v);
                }
            }
        }
        int[] dyn = new int[N];
        int ret = 0; 
        for (Integer v : (ArrayList<Integer>) ord) {
            for (Integer u : (ArrayList<Integer>) radj[v]) {
                dyn[v] = Math.max(dyn[v], dyn[u] + 1);
            }
            ret = Math.max(ret, dyn[v]); 
        }
        System.out.printf("%d\n", ret); 
        stdin.close();
        return; 
    }    
}
