import java.util.*;

public class wettiles {
    public static int[] dirx = { 0, 0, -1, 1 };
    public static int[] diry = { -1, 1, 0, 0 };

    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int X, Y, T, L, W;
        X = stdin.nextInt();
        while (X != -1) {
            Y = stdin.nextInt();
            T = stdin.nextInt();
            L = stdin.nextInt();
            W = stdin.nextInt();
            int[][] grid = new int[X][Y];
            int u, v;
            for (int i = 0; i < L; i++) {
                u = stdin.nextInt() - 1;
                v = stdin.nextInt() - 1;
                grid[u][v] = 1;
            }
            int xa, ya, xb, yb;
            for (int i = 0; i < W; i++) {
                xa = stdin.nextInt() - 1;
                ya = stdin.nextInt() - 1;
                xb = stdin.nextInt() - 1;
                yb = stdin.nextInt() - 1;
                int distx = (xa == xb ? 0 : (-xa + xb) / Math.abs(xa - xb));
                int disty = (ya == yb ? 0 : (-ya + yb) / Math.abs(ya - yb));
                while (xa != xb || ya != yb) {
                    grid[xa][ya] = -1;
                    xa += distx;
                    ya += disty;
                }
                grid[xa][ya] = -1;
            }
            LinkedList<Integer> q = new LinkedList<Integer>();
            for (int i = 0; i < X; i++) {
                for (int j = 0; j < Y; j++) {
                    if (grid[i][j] == 1) {
                        q.add(i * Y + j);
                    }
                }
            }
            int ret = 0;
            while (q.size() > 0) {
                int id = q.poll();
                int x = id / Y, y = id % Y;
                if (grid[x][y] > T) {
                    continue;
                }
                ret++;
                for (int dir = 0; dir < 4; dir++) {
                    int px = x + dirx[dir], py = y + diry[dir];
                    if (0 <= px && px < X && 0 <= py && py < Y && grid[px][py] == 0) {
                        grid[px][py] = grid[x][y] + 1;
                        q.add(px * Y + py);
                    }
                }
            }
            System.out.println(ret);
            X = stdin.nextInt();
            stdin.close();
        }
        return;
    }
}

 
